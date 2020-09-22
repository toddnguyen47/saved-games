#ifndef SRC_UPS_H_
#define SRC_UPS_H_

#include "crc32.hpp"
#include "vector_concat.hpp"

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
  Ups(std::string file_path);
  bool isValidPatch();

private:
  Crc32 crc32_;
  VectorConcat<uint8_t> vector_concat_;
  bool validPatch_;
  std::string file_path_;

  unsigned int original_file_crc32_;
  unsigned int new_file_crc32_;
  unsigned int patch_crc32_;

  unsigned long old_file_size_;
  unsigned long new_file_size_;
  std::vector<unsigned long> changed_offset_list_;
  std::vector<std::vector<uint8_t>> xor_bytes_list_;

  unsigned long decrypt(std::vector<uint8_t> pointer, int index);
  std::vector<uint8_t> encrypt(unsigned long offset);
  std::vector<uint8_t> to_binary();

  /** Ref: https://stackoverflow.com/a/5585683/6323360 */
  std::vector<uint8_t> int_to_bytes(int input);
};

#endif // SRC_UPS_H_
