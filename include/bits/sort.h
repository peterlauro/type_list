#ifndef STDX_BITS_SORT_H
#define STDX_BITS_SORT_H

#include <type_traits.h>
#include <functional>

namespace stdx::detail
{
  template<typename List>
  struct sort_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct sort_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<typename Compare>
    static constexpr auto sort(Compare comp)
    {
      if constexpr (list_type::empty())
      {
        return list_type::create_empty();
      }
      else
      {
        return sort_impl<decltype(list_type::create_empty())>(comp, Ts()...);
      }
    }

  private:
    // insertion sort
    template<typename L, typename Compare, typename T1Sort, typename... TsSort>
    static constexpr auto sort_impl(Compare comp, T1Sort, TsSort... ts)
    {
      constexpr auto predicate = [comp](auto t) constexpr -> bool { return comp(T1Sort{}, t) <= 0; };
      constexpr auto index = L::template find_if(predicate);
      constexpr auto inserted_list = L::template insert<index, T1Sort>();
      return sort_impl<decltype(inserted_list)>(comp, ts...);
    }

    template<typename L, typename Compare>
    static constexpr auto sort_impl(Compare comp)
    {
      return L{};
    }
  };
}

#endif