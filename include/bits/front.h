#ifndef STDX_BITS_FRONT_H
#define STDX_BITS_FRONT_H

namespace stdx::detail
{
  template<typename List>
  struct front_mixin
  {
    static constexpr auto front()
    {
      return front_impl(List{});
    }

  private:
    template<template<typename...> typename L>
    static constexpr auto front_impl(L<>)
    {
      return L<>::create_empty();
    }

    template<template<typename...> typename L, typename T, typename... Ts>
    static constexpr auto front_impl(L<T, Ts...>)
    {
      return T{};
    }
  };
}

#endif
