#ifndef __pym_clonable_hpp
#define __pym_clonable_hpp

#include <concepts>

namespace pym {

template <typename T>
concept clonable = requires(T t) {
    { t.clone() } -> std::convertible_to<T>;
};

} // namespace pym

#endif
