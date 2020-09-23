#ifndef SRC_UPS_H_
#define SRC_UPS_H_

#include "crc32.hpp"
#include "vector_concat.hpp"

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class Ups
{
public:
  Ups();
  bool is_valid_patch(std::vector<uint8_t> ups_path);
  bool is_file_valid_to_apply(std::vector<uint8_t> gba_file);
  std::vector<uint8_t> apply_patch(std::vector<uint8_t> gba_file);

private:
  Crc32 crc32_;
  VectorConcat<unsigned char> vector_concat_;
  bool validPatch_;

  unsigned int original_file_crc32_;
  unsigned int new_file_crc32_;
  unsigned int patch_crc32_;

  unsigned long old_file_size_;
  unsigned long new_file_size_;
  std::vector<unsigned long> changed_offset_list_;
  std::vector<std::vector<uint8_t>> xor_bytes_list_;

  unsigned long decrypt(uint8_t *pointer[]);
  std::vector<uint8_t> encrypt(unsigned long offset);
  std::vector<uint8_t> to_binary();

  /** Ref: https://stackoverflow.com/a/5585683/6323360 */
  std::vector<uint8_t> int_to_bytes_big_endian(int input);
  std::vector<uint8_t> int_to_bytes_little_endian(int input);
};

#endif // SRC_UPS_H_
