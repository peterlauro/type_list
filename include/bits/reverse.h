#ifndef STDX_BITS_REVERSE_H
#define STDX_BITS_REVERSE_H

#include <utility>

namespace stdx::detail
{
  template<typename List>
  struct reverse_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct reverse_mixin<List<Ts...>>
  {
  private:
    using list_type = List<Ts...>;

  public:
    static constexpr auto reverse()
    {
      return list_type::create_empty().push_front(std::declval<Ts>()...);
    }
  };
}

#endif
