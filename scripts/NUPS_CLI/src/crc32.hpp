#ifndef SRC_CRC32_H_
#define SRC_CRC32_H_

#include <cstdint>
#include <iostream>
#include <vector>

class Crc32 {
public:
  Crc32();
  unsigned int crc32_calculate(std::vector<uint8_t> data);

private:
  const unsigned int crc32_table_[256];
  unsigned int crc32_adjust(unsigned int crc32, uint8_t adjust);
};

#endif // SRC_CRC32_H_
