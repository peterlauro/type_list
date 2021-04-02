#ifndef STDX_BITS_REPLACE_H
#define STDX_BITS_REPLACE_H

#include <cstdlib>

namespace stdx::detail
{
  template<typename List>
  struct replace_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct replace_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<typename Old, typename New>
    static constexpr auto replace()
    {
      return list_type::create_list().replace(Old{}, New{});
    }

    template<typename Old, typename New>
    static constexpr auto replace(Old, New)
    {
      if constexpr(list_type::empty() || std::is_same_v<Old, New>)
      {
        return list_type{};
      }
      else if constexpr (std::is_same_v<Old, decltype(list_type::front())>)
      {
        //return list_type::pop_front().push_front(New{}); //replace only the first occurrence of Old
        return list_type::pop_front().push_front(New{}).replace(Old{}, New{});
      }
      else
      {
        constexpr auto rest = list_type::pop_front().replace(Old{}, New{});
        return list_type::create(list_type::front()).push_back(rest);
      }
    }
  };
}

#endif
