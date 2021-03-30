#ifndef STDX_BITS_POPBACK_H
#define STDX_BITS_POPBACK_H

namespace stdx::detail
{
  template<typename List>
  struct pop_back_mixin
  {
    static constexpr auto pop_back()
    {
      if constexpr(List::count() < 2U)
      {
        return List::create_empty();
      }
      else
      {
        return List::create(List::front()).push_back(List::pop_front().pop_back());
      }
    }
  };
}

#endif
