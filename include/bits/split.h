#ifndef STDX_BITS_SPLIT_H
#define STDX_BITS_SPLIT_H

#include <cstdlib>

namespace stdx::detail
{
  template<class List>
  struct split_mixin
  {
    template<std::size_t Idx>
    static constexpr auto split()
    {
      if constexpr (Idx == 0U)
      {
        return List::create(List::create_empty(), List::create_list());
      }
      else if constexpr (Idx >= List::size())
      {
        return List::create(List::create_list(), List::create_empty());
      }
      else
      {
        constexpr auto rest = List::pop_front().template split<Idx - 1U>();
        return List::create(List::flatten(List::front(), rest.front()), rest.second());
      }
    }
  };
}

#endif
