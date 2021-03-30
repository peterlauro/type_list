#ifndef STDX_BIS_PUSHFRONT_H
#define STDX_BIS_PUSHFRONT_H

namespace stdx::detail
{
  template<typename List>
  struct push_front_mixin
  {
    static constexpr auto push_front()
    {
      return List{};
    }

    template<typename T1, typename... Ts>
    static constexpr auto push_front(T1 t1, Ts... ts)
    {
      return push_front_impl(List{}, t1).push_front(ts...);
    }

    template<typename T1, typename... Ts>
    static constexpr auto push_front()
    {
      return push_front_impl(List{}, T1{}).push_front(Ts{}...);
    }

  private:
    template<template<typename...> typename L, typename... Ts, typename... TsPushFront>
    static constexpr auto push_front_impl(L<Ts...>, L<TsPushFront...>)
    {
      return L<TsPushFront..., Ts...>{};
    }

    template<template<typename...> typename L, typename... Ts, class TPushFront>
    static constexpr auto push_front_impl(L<Ts...>, TPushFront)
    {
      return L<TPushFront, Ts...>{};
    }
  };
}

#endif
