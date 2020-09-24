#include "ups.hpp"

Ups::Ups() :
  validPatch_(false),
  old_file_size_(0), new_file_size_(0)
{
}

bool Ups::is_valid_patch(std::vector<uint8_t> ups_file)
{
  this->changed_offset_list_.clear();
  this->xor_bytes_list_.clear();

  uint8_t *ups_ptr = &(ups_file[0]);
  uint8_t *current_ptr = ups_ptr;

  std::string header;
  for (int i = 0; i < 4; i++)
  {
    header.push_back(*current_ptr);
    current_ptr += 1;
  }

  if (header.compare("UPS1") != 0)
    return false;

  this->old_file_size_ = this->decrypt(&current_ptr);
  this->new_file_size_ = this->decrypt(&current_ptr);

  // Body, refactor here! TODO
  unsigned long file_position = 0;
  unsigned int end_of_file_crc_bytes = 12;
  unsigned int end_ptr = static_cast<unsigned int>(ups_file.size()) - end_of_file_crc_bytes;

  while (current_ptr - ups_ptr + 1 < end_ptr)
  {
    if ((current_ptr - ups_ptr + 1) % 128 == 0)
    {
      std::stringstream ss;
      ss << (current_ptr - ups_ptr) << "/" << end_ptr << "\r";
      std::cout << ss.str();
    }

    file_position += this->decrypt(&current_ptr);
    this->changed_offset_list_.push_back(file_position);
    std::vector<uint8_t> new_xor_data;

    while (*current_ptr != 0)
    {
      new_xor_data.push_back(*current_ptr);
      current_ptr += 1;
    }
    this->xor_bytes_list_.push_back(new_xor_data);
    file_position += static_cast<unsigned long>(new_xor_data.size()) + 1;
    current_ptr += 1;
  }
  std::cout << std::endl;

  // End, CRC32
  this->original_file_crc32_ = *(reinterpret_cast<unsigned int *>(current_ptr));
  this->new_file_crc32_ = *(reinterpret_cast<unsigned int *>(current_ptr + 4));
  this->patch_crc32_ = *(reinterpret_cast<unsigned int *>(current_ptr + 8));

  auto binary_byte_vector = this->to_binary();
  unsigned int calculated_crc32 = this->crc32_.crc32_calculate(
                                    binary_byte_vector);

  this->validPatch_ = this->patch_crc32_ == calculated_crc32;

  return this->validPatch_;
}

bool Ups::is_file_valid_to_apply(std::vector<uint8_t> gba_file)
{
  std::cout << "Checking if GBA file is valid" << std::endl;

  unsigned int file_crc32 = this->crc32_.crc32_calculate(gba_file);
  unsigned long gba_filelength = static_cast<unsigned long>(gba_file.size());
  bool fit_as_old = (this->old_file_size_ == gba_filelength)
                    && (file_crc32 == this->original_file_crc32_);
  bool fit_as_new = (this->new_file_size_ == gba_filelength)
                    && (file_crc32 && this->new_file_crc32_);

  std::cout << "Finished: Checking if GBA file is valid" << std::endl;
  return this->validPatch_ && (fit_as_old || fit_as_new);
}

std::vector<uint8_t> Ups::apply_patch(std::vector<uint8_t> gba_file)
{
  unsigned long length = std::max<unsigned long>(static_cast<unsigned long>
                         (gba_file.size()), this->new_file_size_);
  std::vector<uint8_t> result(length);
  unsigned long min_length = std::min<unsigned long>(static_cast<unsigned long>
                             (gba_file.size()), static_cast<unsigned long>(result.size()));

  uint8_t *result_ptr = &result[0];

  auto copy_into_result = [result_ptr, gba_file]
                          (unsigned int start_index,
                           unsigned int end_index)
  {
    for (unsigned int i = start_index; i < end_index; i++)
    {
      result_ptr[i] = gba_file[i];
    }
  };
  unsigned int halfway_index = min_length >> 1;
  const unsigned int max_threads = 4;
  std::vector<std::thread> threads;
  unsigned int shift = max_threads >> 1;
  for (int i = 0; i < max_threads; i++)
  {
    unsigned int temp_len = min_length >> shift;
    unsigned int begin = 0 + (i * temp_len);
    unsigned int end = begin + temp_len;
    if (i == max_threads - 1)
      end = min_length;
    threads.push_back(std::thread(copy_into_result, begin, end));
  }
  for (auto &thread : threads)
    thread.join();

  for (size_t i = 0; i < this->changed_offset_list_.size(); i++)
  {
    for (size_t xor_bytes_len = 0; xor_bytes_len < this->xor_bytes_list_[i].size();
         xor_bytes_len++)
    {
      auto ulong_len = static_cast<unsigned long>(xor_bytes_len);
      result_ptr[this->changed_offset_list_[i] + ulong_len] ^=
        this->xor_bytes_list_[i][xor_bytes_len];
    }

    if (i % 128 == 0)
    {
      std::stringstream ss;
      ss << i << "/" << this->changed_offset_list_.size() << "\r";
      std::cout << ss.str();
    }
  }
  std::cout << std::endl;

  return result;
}

// ---------------------------------------------------------
// | PRIVATE FUNCTIONS
// ---------------------------------------------------------

unsigned long Ups::decrypt(uint8_t *pointer[])
{
  unsigned long value = 0;
  int shift = 1;
  uint8_t x = **pointer;
  *pointer += 1;
  value += static_cast<unsigned long>((x & 0x7F) * shift);

  while ((x & 0x80) == 0)
  {
    shift <<= 7;
    value += static_cast<unsigned long>(shift);
    x = **pointer;
    *pointer += 1;
    value += static_cast<unsigned long>((x & 0x7F) * shift);
  }

  return value;
}

std::vector<uint8_t> Ups::encrypt(unsigned long offset)
{
  std::vector<uint8_t> bytes;

  unsigned long x = offset & 0x7F;
  offset >>= 7;
  while (offset != 0)
  {
    bytes.push_back(static_cast<uint8_t>(x));
    offset -= 1;
    x = offset & 0x7F;
    offset >>= 7;
  }

  bytes.push_back(static_cast<uint8_t>(0x80 | x));
  return bytes;
}

std::vector<uint8_t> Ups::to_binary()
{
  std::vector<uint8_t> byte_vector;
  byte_vector.push_back('U');
  byte_vector.push_back('P');
  byte_vector.push_back('S');
  byte_vector.push_back('1');

  this->vector_concat_.concat(byte_vector, this->encrypt(this->old_file_size_));
  this->vector_concat_.concat(byte_vector, this->encrypt(this->new_file_size_));

  for (int i = 0; i < this->changed_offset_list_.size(); i++)
  {
    unsigned long relative_offset = this->changed_offset_list_[i];
    if (i != 0)
    {
      auto temp_offset = this->changed_offset_list_[i - 1]
                         + this->xor_bytes_list_[i - 1].size() + 1;
      relative_offset -= static_cast<unsigned long>(temp_offset);
    }

    this->vector_concat_.concat(byte_vector, this->encrypt(relative_offset));
    this->vector_concat_.concat(byte_vector, this->xor_bytes_list_[i]);
    byte_vector.push_back(0);
  }

  std::vector<uint8_t> temp_byte_array(4);
  temp_byte_array = this->int_to_bytes_little_endian(this->original_file_crc32_);
  this->vector_concat_.concat(byte_vector, temp_byte_array);
  temp_byte_array = this->int_to_bytes_little_endian(this->new_file_crc32_);
  this->vector_concat_.concat(byte_vector, temp_byte_array);

  return byte_vector;
}

/** Ref: https://stackoverflow.com/a/5585683/6323360 */
std::vector<uint8_t> Ups::int_to_bytes_big_endian(int input)
{
  int max_size = 4;
  std::vector<uint8_t> byte_array(max_size, 0);
  for (int i = 0; i < max_size; i++)
    byte_array[3 - i] = (input >> (i * 8));

  return byte_array;
}

std::vector<uint8_t> Ups::int_to_bytes_little_endian(int input)
{
  std::vector<uint8_t> byte_array = this->int_to_bytes_big_endian(input);
  // Reverse every byte
  size_t lo = 0;
  size_t hi = byte_array.size() - 1;
  while (lo < hi)
  {
    // Double checking since this algorithm WILL fail when lo == hi
    if (lo != hi)
    {
      // Get diff
      byte_array[lo] = byte_array[lo] ^ byte_array[hi];
      // Assign hi; important, assign hi FIRST
      byte_array[hi] = byte_array[lo] ^ byte_array[hi];
      // Assign lo now
      byte_array[lo] = byte_array[lo] ^ byte_array[hi];
      lo += 1;
      hi -= 1;
    }
  }

  return byte_array;
}
