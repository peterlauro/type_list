#ifndef STDX_BITS_FINDIF_H
#define STDX_BITS_FINDIF_H

#include <cstdlib>
#include <functional>
#include <type_traits.h>

namespace stdx::detail
{
  template<typename List>
  struct find_if_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct find_if_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<
      typename UnaryPredicate,
      typename = std::enable_if_t<(stdx::is_constexpr_invocable_r_v<bool, UnaryPredicate, Ts> && ...)>
    >
    static constexpr std::size_t find_if(UnaryPredicate p)
    {
      return list_type::template find_if<0U>(p);
    }

    template<
      std::size_t Pos,
      typename UnaryPredicate,
      typename = std::enable_if_t<(stdx::is_constexpr_invocable_r_v<bool, UnaryPredicate, Ts> && ...)>
    >
    static constexpr std::size_t find_if(UnaryPredicate p)
    {
      if constexpr (list_type::empty() || Pos >= list_type::size())
      {
        return list_type::npos;
      }
      else if constexpr (p(list_type::template get<Pos>()))
      {
        return Pos;
      }
      else
      {
        return list_type::template find_if<Pos + 1U>(p);
      }
    }
  };
}

#endif