#ifndef STDX_BITS_FLATTEN_H
#define STDX_BITS_FLATTEN_H

#include <type_traits>

namespace stdx::detail
{
  //concat
  template<typename List>
  struct flatten_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct flatten_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    static constexpr auto flatten()
    {
      return list_type::create_empty();
    }

    template<typename... ListTs, typename... OtherTs>
    static constexpr auto flatten(List<ListTs...>, OtherTs... others)
    {
      using flatten_type = decltype(list_type::flatten(std::declval<ListTs>()...));
      return flatten_type::push_back(list_type::flatten(others...));
    }

    template<typename T1, typename... OtherTs>
    static constexpr auto flatten(T1, OtherTs... others)
    {
      return List<T1>::push_back(list_type::flatten(others...));
    }
  };
}

#endif
