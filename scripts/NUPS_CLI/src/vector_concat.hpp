#ifndef SRC_VENDOR_CONCAT_H_
#define SRC_VENDOR_CONCAT_H_

#include <vector>

template <typename T>
class VectorConcat
{
public:
  void concat(std::vector<T> vector1, std::vector<T> vector2);
};

#endif // SRC_VENDOR_CONCAT_H_
