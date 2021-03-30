#ifndef STDX_BITS_CONTAINS_H
#define STDX_BITS_CONTAINS_H

#include <type_traits>

namespace stdx::detail
{
  template<typename List>
  struct contains_mixin
  {
    template<typename T>
    static constexpr bool contains(T t)
    {
      if constexpr (List::empty())
      {
        return false;
      }
      else if constexpr (std::is_same_v<T, decltype(List::front())>)
      {
        return true;
      }
      else
      {
        return List::pop_front().contains(t);
      }
    }

    template<typename T>
    static constexpr bool contains()
    {
      if constexpr (List::empty())
      {
        return false;
      }
      else if constexpr (std::is_same_v<T, decltype(List::front())>)
      {
        return true;
      }
      else
      {
        return List::pop_front().template contains<T>();
      }
    }
  };
}

#endif
