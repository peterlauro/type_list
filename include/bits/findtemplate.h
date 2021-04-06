#ifndef STDX_BITS_FINDTEMPLATE_H
#define STDX_BITS_FINDTEMPLATE_H

#include "type_traits.h"

namespace stdx::detail
{
  template<typename List>
  struct find_template_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct find_template_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<typename... Templates,
      typename = std::enable_if_t<(stdx::is_template_v<Templates> && ...)>
    >
    static constexpr auto find_template(Templates... templates)
    {
      if constexpr (list_type::empty())
      {
        return list_type{};
      }
      else if constexpr ((stdx::is_same_template_v<decltype(list_type::front()), Templates> || ...))
      {
        return list_type::create(list_type::front()).push_back(list_type::pop_front().find_template(templates...));
      }
      else
      {
        return list_type::pop_front().find_template(templates...);
      }
    }
  };
}

#endif
