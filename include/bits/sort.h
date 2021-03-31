#ifndef STDX_BITS_SORT_H
#define STDX_BITS_SORT_H

#include <type_traits.h>

namespace stdx::detail
{
  /*
  template<typename List>
  struct sort_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct sort_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<class Compare>
    static constexpr auto sort(Compare comp)
    {
      if constexpr (list_type::empty())
      {
        return list_type{};
      }
      else
      {
        return list_type::create_empty().insert_sort(comp, Ts()...);
      }
    }
  };

  template<typename List>
  struct insert_sort_mixin
  {
    template<typename Compare, typename T1, typename... Ts>
    static constexpr auto insert_sort(Compare comp, T1 t1, Ts... ts)
    {
      constexpr std::size_t index = List::find_if([comp](auto t) { return comp(T1{}, t) <= 0; });
      constexpr auto inserted_list = List::template insert<index>(t1);
      return inserted_list.insert_sort(comp, ts...);
    }

    template<typename Compare>
    static constexpr auto insert_sort(Compare)
    {
      return List{};
    }
  };
  */
  template<typename List>
  struct insert_sort
  {
    template<typename Compare, typename T1, typename... Ts>
    static constexpr auto sort(Compare comp, T1 t1, Ts... ts)
    {
      constexpr std::size_t index = List::find_if([comp](auto t) { return comp(T1{}, t) <= 0; });
      constexpr auto inserted_list = List::template insert<index>(t1);
      return insert_sort<decltype(inserted_list)>::sort(comp, ts...);
    }

    template<typename Compare>
    static constexpr auto sort(Compare)
    {
      return List{};
    }
  };

  template<typename List>
  struct sort_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct sort_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<class Compare>
    static constexpr auto sort(Compare comp)
    {
      if constexpr (list_type::empty())
      {
        return list_type{};
      }
      else
      {
        return insert_sort<decltype(list_type::create_empty())>::sort(comp, Ts()...);
      }
    }
  };
}

#endif
