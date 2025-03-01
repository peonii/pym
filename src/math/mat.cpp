#include "pym/math/mat.hpp"

namespace pym {
template <typename Ty, usize X, usize Y>
const mat2d<Ty, X, Y>
mat2d<Ty, X, Y>::map(std::function<Ty(usize x, usize y)> callback) const {
  mat2d copy = this->clone();

  for (usize i = 0; i < X; i++) {
    for (usize j = 0; j < Y; j++) {
      copy[i, j] = callback(i, j);
    }
  }

  return copy;
}

template <typename Ty, usize X, usize Y>
const lazy_eval_binary<mat2d<Ty, X, Y>, mat2d<Ty, X, Y>, mat2d<Ty, X, Y>>
mat2d<Ty, X, Y>::add(const mat2d<Ty, X, Y> &rhs) const {
  // clang-format off
  return lazy_eval_binary(*this, rhs, [this](const self &lhs, const self &rhs) {
    return lhs.map([lhs, rhs](usize x, usize y) {
      return lhs[x, y] + rhs[x, y];
    });
  });
  // clang-format on
}
} // namespace pym
