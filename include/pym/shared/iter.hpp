#ifndef __pym_iter_hpp
#define __pym_iter_hpp
#include "pym/shared/types.hpp"
#include <type_traits>

namespace pym {
template <typename El, typename Ty> class iterable {
protected:
  inline virtual El &iter_at(usize idx) = 0;
  inline virtual usize iter_begin() = 0;
  inline virtual usize iter_end() = 0;
};

template <typename El, typename Ty> struct is_iterable {
  using value = std::is_base_of<iterable<El, Ty>, Ty>::value;
};

struct iterator_opts {
  bool reverse = false;
  bool loop = false;
};

template <typename El, typename Storage, iterator_opts Opts> class iterator {
  static_assert(is_iterable<El, Storage>::value,
                "storage type must be iterable");

  using self = iterator<El, Storage, Opts>;
  using self_iterable = iterable<El, Storage>;

  Storage &src;
  usize idx;

  inline constexpr self_iterable &_src_iter() { return src; }

  void _check_bounds() {
    if constexpr (!Opts.loop)
      return;

    if constexpr (Opts.reverse) {
      if (idx == -1) {
        idx += _src_iter().iter_end();
      }
    } else {
      if (idx == _src_iter().iter_end()) {
        idx -= _src_iter().iter_end();
      }
    }
  }

public:
  inline self &loopable() {
    return dynamic_cast<iterator<El, Storage,
                                 {
                                     .reverse = Opts.reverse,
                                     .loop = true,
                                 }>>(*this);
  }

  inline El &peek() { return _src_iter().iter_at(idx); }

  inline self &next() {
    if constexpr (Opts.reverse) {
      idx -= 1;
    } else {
      idx += 1;
    }

    _check_bounds();
  }
  inline self &advance(usize i) { return *this; }
};
} // namespace pym

#endif
