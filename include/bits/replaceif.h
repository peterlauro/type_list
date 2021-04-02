#ifndef STDX_BITS_REPLACEIF_H
#define STDX_BITS_REPLACEIF_H

#include <cstdlib>

namespace stdx::detail
{
  template<typename List>
  struct replace_if_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct replace_if_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<typename New, typename UnaryPredicate>
    static constexpr auto replace_if(UnaryPredicate p)
    {
      return list_type::create_list().replace_if(New{}, p);
    }

    template<typename New, typename UnaryPredicate>
    static constexpr auto replace_if(New, UnaryPredicate p)
    {
      if constexpr(list_type::empty())
      {
        return list_type{};
      }
      else if constexpr (p(list_type::front()))
      {
        constexpr auto rest = list_type::pop_front().replace_if(New{}, p);
        return list_type::create(New{}).push_back(rest);
      }
      else
      {
        constexpr auto rest = list_type::pop_front().replace_if(New{}, p);
        return list_type::create(list_type::front()).push_back(rest);
      }
    }
  };
}

#endif
