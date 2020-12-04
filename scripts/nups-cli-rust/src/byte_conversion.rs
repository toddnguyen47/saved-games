pub fn convert_int_to_bytes_big_endian(input: u32) -> Vec<u8> {
  let max_size = 4;
  let mut vec = vec![0; max_size];
  for i in 0..max_size {
    vec[3 - i] = (input >> (i * 8)) as u8;
  }

  vec
}

pub fn convert_int_to_bytes_little_endian(input: u32) -> Vec<u8> {
  let mut byte_array = convert_int_to_bytes_big_endian(input);
  byte_array.reverse();
  byte_array
}
