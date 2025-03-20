#ifndef __pym_lazy_hpp
#define __pym_lazy_hpp
#include <functional>

namespace pym {

template <typename LhsT, typename RhsT = LhsT, typename ResT = LhsT>
class lazy_eval_binary {
    const LhsT& lhs;
    const RhsT& rhs;

    using MapFn = std::function<ResT(const LhsT&, const RhsT&)>;
    MapFn fn;

  public:
    lazy_eval_binary(const LhsT& lhs, const RhsT& rhs, MapFn fn)
        : lhs(lhs), rhs(rhs), fn(fn) {}

    operator ResT() const { return fn(lhs, rhs); }
};

} // namespace pym

#endif
