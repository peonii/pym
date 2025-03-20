#ifndef __pym_arr2d_hpp
#define __pym_arr2d_hpp

#include "pym/shared/types.hpp"
#include "pym/trait/clonable.hpp"

namespace pym {
template <typename Ty, usize X, usize Y> class arr2d {
    using self = arr2d<Ty, X, Y>;

    Ty storage[X * Y];

    constexpr Ty& operator[](usize x, usize y) { return storage[y * X + x]; }

    self clone() {
        self copy;

        for (usize i = 0; i < X * Y; i++) {
            if constexpr (clonable<Ty>) {
                copy.storage[i] = storage[i].clone();
            } else {
                copy.storage[i] = storage[i];
            }
        }

        return copy;
    }
};
}; // namespace pym

#endif
