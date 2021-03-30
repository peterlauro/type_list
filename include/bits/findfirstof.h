#ifndef STDX_BITS_FINDFIRSTOF_H
#define STDX_BITS_FINDFIRSTOF_H

#include <cstdlib>
#include <type_traits>

namespace stdx::detail
{
    template<typename List>
    struct find_first_of_mixin
    {
      template<typename T, std::size_t Pos = 0U>
      static constexpr auto find_first_of()
      {
        if constexpr (List::empty() || Pos >= List::size())
        {
          return List::npos;
        }
        else if constexpr (std::is_same_v<decltype(List::template get<Pos>()), T>)
        {
          return Pos;
        }
        else
        {
          return List::template find_first_of<T, Pos + 1U>();
        }
      }

      template<std::size_t Pos, typename T>
      static constexpr auto find_first_of(T)
      {
        if constexpr (List::empty() || Pos >= List::size())
        {
          return List::npos;
        }
        else if constexpr (std::is_same_v<decltype(List::template get<Pos>()), T>)
        {
          return Pos;
        }
        else
        {
          return List::template find_first_of<Pos + 1U>(T{});
        }
      }

      template<std::size_t Pos, template<typename...> typename L, typename... Ts>
      static constexpr auto find_first_of(L<Ts...>)
      {
        if constexpr (List::empty() || Pos >= List::size() || sizeof...(Ts) == 0U)
        {
          return List::npos;
        }
        else if constexpr ((std::is_same_v<decltype(List::template get<Pos>()), Ts> || ...))
        {
          return Pos;
        }
        else
        {
          return List::template find_first_of<Pos + 1U>(L<Ts...>{});
        }
      }
    };
}

#endif