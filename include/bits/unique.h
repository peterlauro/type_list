#ifndef STDX_BITS_UNIQUE_H
#define STDX_BITS_UNIQUE_H

namespace stdx::detail
{
  template<typename List>
  struct unique_mixin
  {
    static constexpr auto unique()
    {
      return unique_impl(List{});
    }

  private:
    template<typename InL, typename OutL = decltype(InL::create_empty())>
    static constexpr auto unique_impl(InL inList, OutL outList = {})
    {
      if constexpr(!inList.empty())
      {
        return unique_impl(
          inList.pop_front(),
          [&inList, &outList]() constexpr {
            constexpr auto first = inList.front();
            if constexpr(outList.contains(first))
            {
              return outList;
            }
            else
            {
              return outList.push_back(first);
            }
          }());
      }
      else
      {
        return outList;
      }
    }
  };
}

#endif
