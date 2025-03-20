#ifndef __pym_iter_hpp
#define __pym_iter_hpp
#include "pym/shared/types.hpp"
#include <concepts>
#include <type_traits>

namespace pym {

template <typename El, typename Ty>
concept iterable = requires(Ty c, usize idx) {
    { c.iter_at(idx) } -> std::convertible_to<El&>;
    { c.iter_begin() } -> std::same_as<usize>;
    { c.iter_end() } -> std::same_as<usize>;
};

struct iterator_opts {
    bool reverse = false;
    bool loop = false;
};

template <typename El, typename Storage, iterator_opts Opts>
    requires iterable<El, Storage>
class iterator {
    using self = iterator<El, Storage, Opts>;

    Storage& src;
    usize idx;

    void _check_bounds() {
        if constexpr (!Opts.loop)
            return;

        if constexpr (Opts.reverse) {
            if (idx == -1) {
                idx += src.iter_end();
            }
        } else {
            if (idx == src.iter_end()) {
                idx -= src.iter_end();
            }
        }
    }

  public:
    inline self& loopable() {
        return dynamic_cast<iterator<
            El, Storage,
            {
                .reverse = Opts.reverse,
                .loop = true,
            }>>(*this);
    }

    inline El& peek() { return src.iter_at(idx); }

    inline self& next() {
        if constexpr (Opts.reverse) {
            idx -= 1;
        } else {
            idx += 1;
        }

        _check_bounds();
    }
    inline self& advance(usize i) { return *this; }
};
} // namespace pym

#endif
