#ifndef SRC_BYTE_CONVERSION_H_
#define SRC_BYTE_CONVERSION_H_

#include <cstdint>
#include <vector>

namespace byte_conversion {
  /** Ref: https://stackoverflow.com/a/5585683/6323360 */

  /**
   * Convert from int to byte array of size 4. Bytes will be in big endian order.
   * @param input int input to to be converted.
   */
  std::vector<uint8_t> int_to_bytes_big_endian(int input);

  /**
   * Convert from int to byte array of size 4. Bytes will be in little endian order.
   * @param input int input to to be converted.
   */
  std::vector<uint8_t> int_to_bytes_little_endian(int input);

  unsigned int bytes_to_unsigned_int_big_endian(std::vector<uint8_t> bytes);
}

#endif // SRC_BYTE_CONVERSION_H_
