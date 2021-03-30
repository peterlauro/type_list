#ifndef STDX_BITS_POPFRONT_H
#define STDX_BITS_POPFRONT_H

namespace stdx::detail
{
  template<typename List>
  struct pop_front_mixin
  {
    static constexpr auto pop_front()
    {
      return pop_front_impl(List{});
    }

  private:
    template<template<typename...> typename L>
    static constexpr auto pop_front_impl(L<>)
    {
      return L<>::create_list();
    }

    template<template<typename...> typename L, class T, class... Ts>
    static constexpr auto pop_front_impl(L<T, Ts...>)
    {
      return L<Ts...>{};
    }
  };
}

#endif
