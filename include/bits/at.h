#ifndef STDX_BITS_AT_H
#define STDX_BITS_AT_H

#include <cstdlib>

namespace stdx::detail
{
  template<typename List>
  struct at_mixin
  {
    template<std::size_t Idx>
    static constexpr auto at()
    {
      if constexpr (Idx == 0U)
      {
        return List::front();
      }
      else if constexpr (Idx >= List::count())
      {
        return typename List::notype{};
      }
      else
      {
        return List::pop_front().template at<Idx - 1U>();
      }
    }
  };
}

#endif
