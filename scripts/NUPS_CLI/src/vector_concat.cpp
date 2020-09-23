#include "vector_concat.hpp"

template <typename T>
void VectorConcat<T>::concat(std::vector<T> *vector1, std::vector<T> vector2)
{
  vector1->insert(
      vector1->end(),
      std::make_move_iterator(vector2.begin()),
      std::make_move_iterator(vector2.end()));
}

template void VectorConcat<uint8_t>::concat(std::vector<uint8_t> *vector1,
                                            std::vector<uint8_t> vector2);
