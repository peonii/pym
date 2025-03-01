#ifndef __pym_mat_hpp
#define __pym_mat_hpp
#include "pym/math/lazy.hpp"
#include "pym/shared/types.hpp"
#include "pym/trait/clonable.hpp"
#include "pym/util/arr2d.hpp"

namespace pym {

template <typename Ty, usize X, usize Y>
class mat2d : public clonable<mat2d<Ty, X, Y>> {
private:
  using inner_t = arr2d<Ty, X, Y>;
  using self = mat2d<Ty, X, Y>;

  inner_t storage;

  mat2d(inner_t ref) : storage(ref) {}

public:
  constexpr Ty &operator[](usize x, usize y) { return storage[x, y]; }

  const self map(std::function<Ty(size_t y, size_t x)> callback) const;

  [[nodiscard]]
  inline const lazy_eval_binary<self, self, self> add(const mat2d &rhs) const;
  lazy_eval_binary<self, self, self> operator+(const mat2d &rhs) {
    return add(rhs);
  }

  self clone() override { return mat(storage.clone()); }
};
} // namespace pym

#endif
