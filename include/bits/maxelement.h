#ifndef STDX_BITS_MAXELEMENT_H
#define STDX_BITS_MAXELEMENT_H

#include <cstdlib>

namespace stdx::detail
{
  template<typename List>
  struct max_element_mixin;

  template<template<typename...> typename List, typename... Ts>
  struct max_element_mixin<List<Ts...>>
  {
    using list_type = List<Ts...>;

    template<class Compare>
    static constexpr std::size_t max_element(Compare comp)
    {
      if constexpr (list_type::empty())
      {
        return list_type::npos;
      }
      else if constexpr (list_type::size() == 1U)
      {
        return 0U;
      }
      else
      {
        return max_element_impl<0U, 1U>(comp);
      }
    }

  private:
    template<std::size_t LargestIdx, std::size_t Idx, typename Compare>
    static constexpr std::size_t max_element_impl(Compare comp)
    {
      if constexpr (Idx < list_type::size())
      {
        if constexpr (comp(list_type::template get<LargestIdx>(), list_type::template get<Idx>()))
        {
          return max_element_impl<Idx, Idx + 1U>(comp);
        }
        else
        {
          return max_element_impl<LargestIdx, Idx + 1U>(comp);
        }
      }
      else
      {
        return LargestIdx;
      }
    }
  };
}

#endif
