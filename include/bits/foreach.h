#ifndef STDX_BITS_FOREACH_H
#define STDX_BITS_FOREACH_H

#include <type_traits>
#include <utility>

namespace stdx::detail
{
  template<typename List>
  struct for_each_mixin
  {
    template<typename UnaryFunction>
    static constexpr bool for_each([[maybe_unused]] UnaryFunction f)
    {
      if constexpr(List::empty())
      {
        return true;
      }
      else
      {
        if constexpr(std::is_invocable_r_v<bool, UnaryFunction, decltype(List::front())>)
        {
          if (f(List::front()))
          {
            return false;
          }
        }
        else
        {
          f(List::front());
        }

        return List::pop_front().for_each(std::move(f));
      }
    }
  };
}

#endif
