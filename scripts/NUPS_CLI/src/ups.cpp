#include "ups.hpp"

Ups::Ups(std::string file_path) : file_path_(file_path), validPatch_(false),
                                  old_file_size_(0), new_file_size_(0)
{
}

bool Ups::isValidPatch()
{
  this->changed_offset_list_.clear();
  this->xor_bytes_list_.clear();

  std::ifstream input_stream(this->file_path_, std::ios::binary);
  // copies all data into buffer
  std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input_stream), {});

  int current_ptr = 0;
  std::string header;
  while (current_ptr < 4)
  {
    header.push_back(buffer[current_ptr]);
    current_ptr += 1;
  }

  if (header.compare("UPS1") != 0)
    return false;

  this->old_file_size_ = this->decrypt(buffer, current_ptr);
  this->new_file_size_ = this->decrypt(buffer, current_ptr);

  // // Body, refactor here! TODO
  unsigned long file_position = 0;
  int end_of_file_crc_bytes = 12;
  std::cout << "Buffer size: " << buffer.size() << std::endl;
  while (current_ptr + 1 < buffer.size() - end_of_file_crc_bytes)
  {
    file_position += this->decrypt(buffer, current_ptr);
    this->changed_offset_list_.push_back(file_position);
    std::vector<uint8_t> new_xor_data;

    while (buffer[current_ptr] != 0)
    {
      new_xor_data.push_back(buffer[current_ptr]);
      current_ptr += 1;
    }
    this->xor_bytes_list_.push_back(new_xor_data);
    file_position += static_cast<unsigned long>(new_xor_data.size()) + 1;
    current_ptr += 1;
  }

  // End, CRC32
  this->original_file_crc32_ = buffer[current_ptr];
  this->new_file_crc32_ = buffer[current_ptr + 4];
  this->patch_crc32_ = buffer[current_ptr + 8];

  unsigned int calculated_crc32 = this->crc32_.crc32_calculate(this->to_binary());

  for (size_t i = buffer.size() - 1; i > buffer.size() - 5; i--)
    printf("0x%02X\n", buffer[i]);
  std::cout << "Patch: " << this->patch_crc32_ << std::endl;
  std::cout << "Calculated: " << calculated_crc32 << std::endl;

  return this->validPatch_;
}

// ****************************************************************************
// | PRIVATE FUNCTIONS
// ****************************************************************************

unsigned long Ups::decrypt(std::vector<uint8_t> data, int index)
{
  unsigned long value = 0;
  int shift = 1;
  uint8_t x = data[index];
  index += 1;
  value += static_cast<unsigned long>((x & 0x7F) * shift);

  while ((x & 0x80) == 0)
  {
    shift <<= 7;
    value += static_cast<unsigned long>(shift);
    x = data[index];
    index += 1;
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

  this->vector_concat_.concat(&byte_vector, this->encrypt(this->old_file_size_));
  this->vector_concat_.concat(&byte_vector, this->encrypt(this->new_file_size_));

  for (int i = 0; i < this->changed_offset_list_.size(); i++)
  {
    unsigned long relative_offset = this->changed_offset_list_[i];
    if (i != 0)
    {
      auto temp_offset = this->changed_offset_list_[i - 1] + this->xor_bytes_list_[i - 1].size() + 1;
      relative_offset = static_cast<unsigned long>(temp_offset);
    }

    this->vector_concat_.concat(&byte_vector, this->encrypt(relative_offset));
    this->vector_concat_.concat(&byte_vector, this->xor_bytes_list_[i]);
    byte_vector.push_back(0);
  }

  this->vector_concat_.concat(&byte_vector, this->int_to_bytes(this->original_file_crc32_));
  this->vector_concat_.concat(&byte_vector, this->int_to_bytes(new_file_crc32_));

  return byte_vector;
}

/** Ref: https://stackoverflow.com/a/5585683/6323360 */
std::vector<uint8_t> Ups::int_to_bytes(int input)
{
  std::vector<uint8_t> byte_array;
  for (int i = 0; i < 4; i++)
    byte_array[3 - i] = (input >> (i * 8));
  return byte_array;
}
