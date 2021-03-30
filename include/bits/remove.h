#ifndef STDX_BITS_REMOVE_H
#define STDX_BITS_REMOVE_H

namespace stdx::detail
{
  template<typename List>
  struct remove_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct remove_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    static constexpr auto remove()
    {
      return list_type{};
    }

    template<typename T1, typename... TsRemove>
    static constexpr auto remove()
    {
      return remove(list_type::template create<T1, TsRemove...>());
    }

    template<typename T1, typename... TsRemove>
    static constexpr auto remove(T1 t1, TsRemove... ts)
    {
      return remove(list_type::create(t1, ts...));
    }

    template<typename... TsRemove>
    static constexpr auto remove(List<TsRemove...> listRemove)
    {
      if constexpr(list_type::empty())
      {
        return list_type::create_empty();
      }

      if constexpr(listRemove.template contains<decltype(list_type::front())>())
      {
        return list_type::pop_front().remove(listRemove);
      }
      else
      {
        return list_type::create_empty().push_back(list_type::front()).push_back(list_type::pop_front().remove(listRemove));
      }
    }
  };
}

#endif
