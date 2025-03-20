#ifndef __pym_result_hpp
#define __pym_result_hpp

#include "pym/shared/types.hpp"
#include <concepts>
#include <functional>
#include <stdexcept>
#include <type_traits>

namespace pym {

template <typename T, typename E>
    requires std::destructible<T> && std::destructible<E>
class result {
  private:
    enum class tag_t : u8 { ok, err };

    tag_t tag;
    union {
        T success;
        E error;
    } value;

    using self = result<T, E>;

    result(tag_t tag, T success) : tag(tag), value(success) {}
    result(tag_t tag, E error) : tag(tag), value(error) {}

  public:
    constexpr bool is_ok() { return tag == tag_t::ok; }
    constexpr bool is_err() { return tag == tag_t::err; }
    constexpr operator bool() { return is_ok(); }

    constexpr T& unwrap() const {
        if (tag == tag_t::err) {
            throw std::runtime_error("tried to unwrap an err value");
        }

        return value.success;
    }

    constexpr E& unwrap_err() const {
        if (tag == tag_t::ok) {
            throw std::runtime_error("tried to unwrap err an ok value");
        }

        return value.success;
    }

    template <typename Op>
        requires std::invocable<Op, T>
    constexpr result<std::invoke_result_t<Op, T>, E> map(Op f) const {
        if (tag == tag_t::err)
            return std::move(*this);

        return result(tag, f(std::move(value.success)));
    }

    template <typename F>
        requires std::destructible<F>
    constexpr result<T, F> map_err(std::function<F(E)> f) const {
        if (tag == tag_t::ok)
            return std::move(*this);

        return result(tag, f(std::move(value.error)));
    }

    inline static constexpr self ok(T val) { return result(tag_t::ok, val); }
    inline static constexpr self err(T val) { return result(tag_t::err, val); }
};

} // namespace pym

#endif
