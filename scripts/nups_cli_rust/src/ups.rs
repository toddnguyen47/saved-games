use byteorder::ReadBytesExt;
use std::io::Cursor;

use crate::byte_conversion;
use crate::crc32::Crc32;

#[derive(Debug)]
pub struct Ups {
  valid_patch_: bool,
  old_file_size_: u32,
  new_file_size_: u32,
  changed_offset_list_: Vec<u32>,
  xor_bytes_list_: Vec<Vec<u8>>,
  current_ptr_: u32,
  crc32_struct_: Crc32Nums,
  crc32_: Crc32,
}

#[derive(Debug)]
struct Crc32Nums {
  original_file: u32,
  new_file: u32,
  patch: u32,
}

impl Ups {
  pub fn new(crc32: Crc32) -> Ups {
    Ups {
      valid_patch_: false,
      old_file_size_: 0,
      new_file_size_: 0,
      changed_offset_list_: Vec::<u32>::new(),
      xor_bytes_list_: Vec::<Vec<u8>>::new(),
      current_ptr_: 0,
      crc32_struct_: Crc32Nums {
        original_file: 0,
        new_file: 0,
        patch: 0,
      },
      crc32_: crc32,
    }
  }

  pub fn is_valid_patch(&mut self, ups_file: &[u8]) -> Result<(), anyhow::Error> {
    println!("Checking if patch is valid.");
    self.changed_offset_list_.clear();
    self.xor_bytes_list_.clear();

    let mut header = String::from("");

    while self.current_ptr_ < 4 {
      header.push(ups_file[self.current_ptr_ as usize] as char);
      self.current_ptr_ += 1;
    }

    if header != "UPS1" {
      return Err(anyhow::anyhow!("ERROR: Header is not 'UPS1'"));
    }

    self.old_file_size_ = self.decrypt(ups_file);
    self.new_file_size_ = self.decrypt(ups_file);

    let mut file_position: u32 = 0;
    let end_of_file_crc_bytes: u32 = 12;
    let end_ptr = ups_file.len() as u32 - end_of_file_crc_bytes;

    self.set_changed_offsets_and_xor_bytes(ups_file, &mut file_position, &end_ptr);
    self.check_valid_base_on_crc32(ups_file)
  }

  pub fn is_file_valid_to_apply(&self, gba_file: &[u8]) -> Result<(), anyhow::Error> {
    println!("Checking if GBA file is valid...");
    let file_crc32 = self.crc32_.crc32_calculate(gba_file);
    let gba_filelength = gba_file.len() as u32;
    let fit_as_old =
      self.old_file_size_ == gba_filelength && file_crc32 == self.crc32_struct_.original_file;
    let fit_as_new =
      self.new_file_size_ == gba_filelength && file_crc32 == self.crc32_struct_.new_file;

    let results = self.valid_patch_ && (fit_as_old || fit_as_new);
    println!("FINISHED: Checking if GBA file is valid...");
    match results {
      true => Ok(()),
      false => Err(anyhow::anyhow!("GBA file is NOT valid!")),
    }
  }

  pub fn apply_patch(&self, gba_file: &[u8]) -> Vec<u8> {
    let length = std::cmp::max(gba_file.len(), self.new_file_size_ as usize);
    let mut patched_gba_file = vec![0; length];
    let min_length = std::cmp::min(gba_file.len(), length);

    for i in 0..min_length {
      patched_gba_file[i] = gba_file[i];
    }

    for i in 0..self.changed_offset_list_.len() {
      for j in 0..self.xor_bytes_list_[i].len() {
        let index = self.changed_offset_list_[i] as usize + j;
        patched_gba_file[index] ^= self.xor_bytes_list_[i][j];
      }
    }

    patched_gba_file
  }

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // | PRIVATE FUNCTIONS
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  fn decrypt(&mut self, ups_file: &[u8]) -> u32 {
    let mut value: u32 = 0;
    let mut shift: u32 = 1;
    let mut x = ups_file[self.current_ptr_ as usize];
    self.current_ptr_ += 1;
    value += (x & 0x7F) as u32 * shift;

    while (x & 0x80) == 0 {
      shift <<= 7;
      value += shift as u32;
      x = ups_file[self.current_ptr_ as usize];
      self.current_ptr_ += 1;
      value += (x & 0x7F) as u32 * shift;
    }

    value
  }

  fn encrypt(&self, offset: u32) -> Vec<u8> {
    let mut bytes = Vec::<u8>::new();
    let mut x: u32 = offset & 0x7F;
    let mut offset: u32 = offset >> 7;

    while offset != 0 {
      bytes.push(x as u8);
      offset -= 1;
      x = offset & 0x7F;
      offset >>= 7;
    }

    let final_byte = (0x80 | x) as u8;
    bytes.push(final_byte);
    bytes
  }

  fn set_ups_crc32(&mut self, ups_file: &[u8]) {
    let ptr = self.current_ptr_ as usize;

    let mut cursor = Cursor::new(&ups_file[ptr + 0..ptr + 4]);
    self.crc32_struct_.original_file = cursor.read_u32::<byteorder::LittleEndian>().unwrap();

    let mut cursor = Cursor::new(&ups_file[ptr + 4..ptr + 8]);
    self.crc32_struct_.new_file = cursor.read_u32::<byteorder::LittleEndian>().unwrap();

    let mut cursor = Cursor::new(&ups_file[ptr + 8..ptr + 12]);
    self.crc32_struct_.patch = cursor.read_u32::<byteorder::LittleEndian>().unwrap();
  }

  fn to_binary(&self) -> Vec<u8> {
    let mut byte_vector = Vec::<u8>::new();
    byte_vector.push('U' as u8);
    byte_vector.push('P' as u8);
    byte_vector.push('S' as u8);
    byte_vector.push('1' as u8);

    byte_vector.extend(&self.encrypt(self.old_file_size_));
    byte_vector.extend(&self.encrypt(self.new_file_size_));

    for i in 0..self.changed_offset_list_.len() {
      let mut relative_offset = self.changed_offset_list_[i];
      if i != 0 {
        let temp_offset =
          self.changed_offset_list_[i - 1] + (self.xor_bytes_list_[i - 1].len() as u32) + 1;
        relative_offset -= temp_offset;
      }

      byte_vector.extend(&self.encrypt(relative_offset));
      byte_vector.extend(&self.xor_bytes_list_[i]);
      byte_vector.push(0u8);
    }

    byte_vector.extend(byte_conversion::convert_int_to_bytes_little_endian(
      self.crc32_struct_.original_file,
    ));

    byte_vector.extend(byte_conversion::convert_int_to_bytes_little_endian(
      self.crc32_struct_.new_file,
    ));

    byte_vector
  }

  fn set_changed_offsets_and_xor_bytes(
    &mut self,
    ups_file: &[u8],
    file_position: &mut u32,
    end_ptr: &u32,
  ) {
    while self.current_ptr_ + 1 < *end_ptr {
      *file_position += self.decrypt(ups_file);
      self.changed_offset_list_.push(*file_position as u32);
      let mut new_xor_data = Vec::<u8>::new();

      while ups_file[self.current_ptr_ as usize] != 0 {
        new_xor_data.push(ups_file[self.current_ptr_ as usize]);
        self.current_ptr_ += 1;
      }

      let new_xor_len = new_xor_data.len();
      self.xor_bytes_list_.push(new_xor_data);
      *file_position += (new_xor_len as u32) + 1;
      self.current_ptr_ += 1;
    }
  }

  fn check_valid_base_on_crc32(&mut self, ups_file: &[u8]) -> Result<(), anyhow::Error> {
    self.set_ups_crc32(ups_file);
    let binary_byte_vector = self.to_binary();
    let calculated_crc32 = self.crc32_.crc32_calculate(&binary_byte_vector);
    self.valid_patch_ = calculated_crc32 == self.crc32_struct_.patch;
    println!("FINISHED: Checking if patch is valid.");
    match self.valid_patch_ {
      true => Ok(()),
      false => Err(anyhow::anyhow!("Patch was not valid")),
    }
  }
}
