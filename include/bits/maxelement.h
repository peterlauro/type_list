#ifndef STDX_BITS_MAXELEMENT_H
#define STDX_BITS_MAXELEMENT_H

#include <cstdlib>

namespace stdx::detail
{
  template<typename List>
  struct max_element_mixin
  {
    template<class Compare>
    static constexpr std::size_t max_element(Compare comp)
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
        return max_element_impl<0U, 1U>(comp);
      }
    }

  private:
    template<std::size_t LargestIdx, std::size_t Idx, typename Compare>
    static constexpr std::size_t max_element_impl(Compare comp)
    {
      if constexpr (Idx < List::size())
      {
        if constexpr (comp(List::template get<LargestIdx>(), List::template get<Idx>()))
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
