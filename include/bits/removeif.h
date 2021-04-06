#ifndef STDX_BITS_REMOVEIF_H
#define STDX_BITS_REMOVEIF_H

#include "type_traits.h"

namespace stdx::detail
{
  template<typename List>
  struct remove_if_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct remove_if_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<
      typename UnaryPredicate,
      typename = std::enable_if_t<(stdx::is_constexpr_invocable_r_v<bool, UnaryPredicate, Ts> && ...)>
    >
    static constexpr auto remove_if(UnaryPredicate p)
    {
      if constexpr (list_type::empty())
      {
        return list_type{};
      }
      else if constexpr (p(list_type::front()))
      {
        return list_type::pop_front().remove_if(p);
      }
      else
      {
        return list_type::create(list_type::front()).push_back(list_type::pop_front().remove_if(p));
      }
    }
  };
}

#endif
