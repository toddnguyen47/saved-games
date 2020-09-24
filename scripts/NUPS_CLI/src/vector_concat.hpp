#ifndef SRC_VENDOR_CONCAT_H_
#define SRC_VENDOR_CONCAT_H_

#include <vector>
#include <cstdint>

template <typename T>
class VectorConcat
{
public:
  inline void concat(std::vector<T> &vector1, std::vector<T> &vector2);
};

template <typename T>
void VectorConcat<T>::concat(std::vector<T> &vector1, std::vector<T> &vector2)
{
  vector1.insert(
    vector1.end(),
    std::make_move_iterator(vector2.begin()),
    std::make_move_iterator(vector2.end()));
}

#endif // SRC_VENDOR_CONCAT_H_
