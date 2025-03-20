#ifndef __pym_mat_hpp
#define __pym_mat_hpp
#include "pym/math/lazy.hpp"
#include "pym/shared/types.hpp"
#include "pym/util/arr2d.hpp"

namespace pym {

template <typename Ty, usize X, usize Y> class mat2d {
  private:
    using inner_t = arr2d<Ty, X, Y>;
    using self = mat2d<Ty, X, Y>;

    inner_t storage;

    mat2d(inner_t ref) : storage(ref) {}

  public:
    constexpr Ty& operator[](usize x, usize y) { return storage[x, y]; }

    self map(std::function<Ty(usize y, usize x)> callback) const;

    [[nodiscard]]
    inline lazy_eval_binary<self> add(const mat2d& rhs) const;
    lazy_eval_binary<self> operator+(const mat2d& rhs) { return add(rhs); }

    self clone() { return mat2d(storage.clone()); }
};
} // namespace pym

#endif
