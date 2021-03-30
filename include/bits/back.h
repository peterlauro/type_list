#ifndef STDX_BITS_BACK_H
#define STDX_BITS_BACK_H

namespace stdx::detail
{
  template<typename List>
  struct back_mixin
  {
    static constexpr auto back()
    {
      if constexpr (List::count() < 2U)
      {
        return List::front();
      }
      else
      {
        return List::pop_front().back();
      }
    }
  };
}

#endif
