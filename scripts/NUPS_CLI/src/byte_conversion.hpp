#ifndef SRC_BYTE_CONVERSION_H_
#define SRC_BYTE_CONVERSION_H_

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

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

  /**
   * Convert bytes to unsigned int. Bytes will be expected to be in big endian.
   *
   * @param bytes big endian byte array.
   * @param start_index the index of the starting byte.
   * @param byte_length the length of our current byte.
   */
  unsigned int bytes_to_uint_big_endian(
    const std::vector<uint8_t> &bytes, const unsigned int start_index,
    const unsigned int byte_length);

  /**
  * Convert bytes to unsigned int. Bytes will be expected to be in little endian.
  *
  * @param bytes big endian byte array.
  * @param start_index the index of the starting byte.
  * @param byte_length the length of our current byte.
  */
  unsigned int bytes_to_uint_little_endian(
    const std::vector<uint8_t> &bytes, const unsigned int start_index,
    const unsigned int byte_length);
}

#endif // SRC_BYTE_CONVERSION_H_
