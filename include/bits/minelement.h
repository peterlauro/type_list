#ifndef STDX_BITS_MINELEMENT_H
#define STDX_BITS_MINELEMENT_H

#include <cstdlib>

namespace stdx::detail
{
  template<typename List>
  struct min_element_mixin
  {
    template<class Compare>
    static constexpr std::size_t min_element(Compare comp)
    {
      if constexpr (List::empty())
      {
        return List::npos;
      }
      else if constexpr (List::size() == 1U)
      {
        return 0U;
      }
      else
      {
        return min_element_impl<0U, 1U>(comp);
      }
    }

  private:
    template<std::size_t SmallestIdx, std::size_t Idx, typename Compare>
    static constexpr std::size_t min_element_impl(Compare comp)
    {
      if constexpr (Idx < List::size())
      {
        if constexpr (comp(List::template get<Idx>(), List::template get<SmallestIdx>()))
        {
          return min_element_impl<Idx, Idx + 1U>(comp);
        }
        else
        {
          return min_element_impl<SmallestIdx, Idx + 1U>(comp);
        }
      }
      else
      {
        return SmallestIdx;
      }
    }
  };
}

#endif
