#ifndef SRC_VENDOR_CONCAT_H_
#define SRC_VENDOR_CONCAT_H_

#include <vector>
#include <cstdint>

namespace vector_concat {

  /**
   * Insert elements of `vector2` at the end of `vector1`
   * @param vector1: Main vector
   * @param vector2: Vector to be appended to `vector1`
   */
  template <typename T>
  void concat(std::vector<T> &vector1, const std::vector<T> &vector2) {
    vector1.insert(
      vector1.end(),
      std::make_move_iterator(vector2.begin()),
      std::make_move_iterator(vector2.end()));
  }
}

#endif // SRC_VENDOR_CONCAT_H_
