#include "byte_conversion.hpp"

namespace byte_conversion {
  /** Ref: https://stackoverflow.com/a/5585683/6323360 */
  std::vector<uint8_t> int_to_bytes_big_endian(int input) {
    int max_size = 4;
    std::vector<uint8_t> byte_array(max_size, 0);
    for (int i = 0; i < max_size; i++)
      byte_array[3 - i] = (input >> (i * 8));

    return byte_array;
  }

  std::vector<uint8_t> int_to_bytes_little_endian(int input) {
    std::vector<uint8_t> byte_array = byte_conversion::int_to_bytes_big_endian(input);
    // Reverse every byte
    size_t lo = 0;
    size_t hi = byte_array.size() - 1;
    while (lo < hi) {
      // Double checking since this algorithm WILL fail when lo == hi
      if (lo != hi) {
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
}
