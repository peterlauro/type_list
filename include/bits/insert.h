#ifndef STDX_BITS_INSERT_H
#define STDX_BITS_INSERT_H

#include <cstdlib>

namespace stdx::detail
{
  template<class List>
  struct insert_mixin
  {
    template<std::size_t Idx, typename... Ts>
    static constexpr auto insert(Ts... ts)
    {
      if constexpr (Idx == 0U)
      {
        return List::template create<Ts...>().template push_back<List>();
      }
      else if constexpr(Idx >= List::count())
      {
        return List::create_list().push_back(ts...);
      }
      else
      {
        constexpr auto split_list = List::template split<Idx>();
        return split_list.front().push_back(ts...).push_back(split_list.second());
      }
    }

    template<std::size_t Idx, typename... Ts>
    static constexpr auto insert()
    {
      if constexpr (Idx == 0U)
      {
        return List::template create<Ts...>().template push_back<List>();
      }
      if constexpr (Idx >= List::count())
      {
        return List::create_list().template push_back<Ts...>();
      }
      else
      {
        constexpr auto split_list = List::template split<Idx>();
        return split_list.front().template push_back<Ts...>().push_back(split_list.second());
      }
    }
  };
}

#endif
