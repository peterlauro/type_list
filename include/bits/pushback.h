#ifndef STDX_BITS_PUSHBACK_H
#define STDX_BITS_PUSHBACK_H

namespace stdx::detail
{
  template<typename List>
  struct push_back_mixin
  {
    static constexpr auto push_back()
    {
      return List::create_list();
    }

    template<typename T1, typename... Ts>
    static constexpr auto push_back(T1 t1, Ts... ts)
    {
      return push_back_impl(List{}, t1).push_back(ts...);
    }

    template<typename T1, typename... Ts>
    static constexpr auto push_back()
    {
      return push_back_impl(List{}, T1{}).push_back(Ts{}...);
    }

  private:
    template<template<typename...> typename L, typename... Ts, typename... TsPushBack>
    static constexpr auto push_back_impl(L<Ts...>, L<TsPushBack...>)
    {
      return L<Ts..., TsPushBack...>{};
    }

    template<template<typename...> typename L, typename... Ts, class TPushBack>
    static constexpr auto push_back_impl(L<Ts...>, TPushBack)
    {
      return L<Ts..., TPushBack>{};
    }
  };
} 

#endif
