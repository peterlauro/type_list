#ifndef STDX_TYPE_LIST_H
#define STDX_TYPE_LIST_H

#include <bits/at.h>
#include <bits/back.h>
#include <bits/contains.h>
#include <bits/filter.h>
#include <bits/findfirstnotof.h>
#include <bits/findfirstof.h>
#include <bits/findif.h>
#include <bits/findifnot.h>
#include <bits/findlastnotof.h>
#include <bits/findlastof.h>
#include <bits/flatten.h>
#include <bits/foreach.h>
#include <bits/front.h>
#include <bits/get.h>
#include <bits/insert.h>
#include <bits/popback.h>
#include <bits/popfront.h>
#include <bits/pushback.h>
#include <bits/pushfront.h>
#include <bits/remove.h>
#include <bits/removeif.h>
#include <bits/reverse.h>
#include <bits/second.h>
#include <bits/sort.h>
#include <bits/split.h>
#include <bits/unique.h>

#include <type_traits.h>
#include <tuple>

namespace stdx
{
  namespace detail
  {
    struct type_list_common
    {
      struct notype
      {
      };

      static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    };

    template<template<typename...> typename List, typename... Ts>
    struct type_list_base
      : type_list_common
      , at_mixin<List<Ts...>>
      , back_mixin<List<Ts...>>
      , contains_mixin<List<Ts...>>
      , filter_mixin<List<Ts...>>
      , find_first_not_of_mixin<List<Ts...>>
      , find_first_of_mixin<List<Ts...>>
      , find_if_mixin<List<Ts...>>
      , find_if_not_mixin<List<Ts...>>
      , find_last_not_of_mixin<List<Ts...>>
      , find_last_of_mixin<List<Ts...>>
      , flatten_mixin<List<Ts...>>
      , for_each_mixin<List<Ts...>>
      , front_mixin<List<Ts...>>
      , get_mixin<List<Ts...>>
      , insert_mixin<List<Ts...>>
      , pop_back_mixin<List<Ts...>>
      , pop_front_mixin<List<Ts...>>
      , push_back_mixin<List<Ts...>>
      , push_front_mixin<List<Ts...>>
      , remove_mixin<List<Ts...>>
      , remove_if_mixin<List<Ts...>>
      , reverse_mixin<List<Ts...>>
      , second_mixin<List<Ts...>>
      , sort_mixin<List<Ts...>>
      , split_mixin<List<Ts...>>
      , unique_mixin<List<Ts...>>
    {
      static_assert((is_constexpr_default_constructible_v<Ts> && ...),
        "Only literal types are supported");

      using list_type = List<Ts...>;
      using self_type = type_list_base;

      /**
       * \brief Returns the number of type elements in the type_list
       * \return number of type elements in the type_list
       */
      static constexpr std::size_t count() noexcept
      {
        return sizeof...(Ts);
      }

      static constexpr std::size_t size() noexcept
      {
        return count();
      }

      static constexpr bool empty() noexcept
      {
        return count() == 0U;
      }

      template<typename... ListElems>
      static constexpr auto create()
      {
        return List<ListElems...>{};
      }

      template<typename... ListElems>
      static constexpr auto create(ListElems...)
      {
        return List<ListElems...>{};
      }

      static constexpr auto create_list()
      {
        return list_type{};
      }

      static constexpr auto create_empty()
      {
        return create<>();
      }

      static constexpr std::tuple<Ts...> to_tuple()
      {
        return {};
      }
    };
  }

  template<typename... Ts>
  struct type_list : detail::type_list_base<type_list, Ts...>
  {
    constexpr type_list() = default;
    constexpr type_list(Ts...) {}
  };

  template<>
  struct type_list<> : detail::type_list_base<type_list>
  {
  };

  using empty_type_list = type_list<>;
  inline constexpr empty_type_list empty_type_list_v;

  template<typename... Ts>
  constexpr auto make_type_list()
  {
    return type_list<Ts...>{};
  }

  template<typename... Ts>
  constexpr auto make_type_list(Ts&&...)
  {
    return type_list<Ts...>{};
  }

  template<typename... Ts>
  constexpr std::tuple<Ts...> to_tuple(type_list<Ts...>)
  {
    return {};
  }

  template<typename... Ts>
  type_list(Ts...) -> type_list<Ts...>;
}

#endif