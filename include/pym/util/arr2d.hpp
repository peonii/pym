#ifndef __pym_arr2d_hpp
#define __pym_arr2d_hpp

#include "pym/shared/types.hpp"
#include "pym/trait/clonable.hpp"

namespace pym {
template <typename Ty, usize X, usize Y>
class arr2d : public clonable<arr2d<Ty, X, Y>> {
  using self = arr2d<Ty, X, Y>;

  Ty storage[X * Y];

  constexpr Ty &operator[](usize x, usize y) { return storage[y * X + x]; }

  self clone() override {
    self copy;

    for (usize i = 0; i < X * Y; i++) {
      copy.storage[i] = storage[i];
    }

    return copy;
  }
};
}; // namespace pym

#endif
