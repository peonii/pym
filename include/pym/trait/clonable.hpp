#ifndef __pym_clonable_hpp
#define __pym_clonable_hpp

namespace pym {
template <typename Ty> struct clonable {
  // Create a deep clone of an object.
  virtual Ty clone() = 0;
};
} // namespace pym

#endif
