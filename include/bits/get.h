#ifndef STDX_BITS_GET_H
#define STDX_BITS_GET_H

#include <cstdlib>

namespace stdx::detail
{
  template<class List>
  struct get_mixin
  {
    template<std::size_t Idx>
    static constexpr auto get()
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
        return List::pop_front().template get<Idx - 1U>();
      }
    }
  };
}

#endif