#ifndef STDX_BITS_SECOND_H
#define STDX_BITS_SECOND_H

namespace stdx::detail
{
  template<typename List>
  struct second_mixin
  {
    static constexpr auto second()
    {
      return List::pop_front().front();
    }
  };
}

#endif
