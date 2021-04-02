#ifndef STDX_BITS_TRANSFORM_H
#define STDX_BITS_TRANSFORM_H

namespace stdx::detail
{
  template<typename List>
  struct transform_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct transform_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<typename UnaryOperation>
    static constexpr auto transform(UnaryOperation op)
    {
      if constexpr(list_type::empty())
      {
        return list_type{};
      }
      else
      {
        constexpr auto rest = list_type::pop_front().transform(op);
        return list_type::create(op(list_type::front())).push_back(rest);
      }
    }
  };
}

#endif
