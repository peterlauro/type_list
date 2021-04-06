#ifndef STDX_TYPE_TRAITS_H
#define STDX_TYPE_TRAITS_H

#include <type_traits>

namespace stdx
{
  namespace detail
  {
    template<typename T>
    static constexpr auto init_is_constexpr_default_constructible_(T)
    {
      return true;
    }

    template<typename T, bool = init_is_constexpr_default_constructible_(T{})>
    static void is_constexpr_default_constructible_();
  }

  template<typename T, typename = std::void_t<>>
  struct is_constexpr_default_constructible : std::false_type
  {
  };

  template<typename T>
  struct is_constexpr_default_constructible<
    T,
    std::void_t<decltype(detail::is_constexpr_default_constructible_<T>())>
  >
    : std::true_type
  {
  };

  template<typename T>
  inline constexpr bool is_constexpr_default_constructible_v =
    is_constexpr_default_constructible<T>::value;

  template<typename T>
  inline constexpr bool is_constexpr_nothrow_default_constructible_v =
    std::is_nothrow_constructible_v<T> && is_constexpr_default_constructible<T>::value;

  namespace detail
  {
    template<typename...>
    struct tag_t {};

    template<typename...Ts>
    inline constexpr tag_t<Ts...> tag{};

    template<typename T, typename... Args>
    struct is_constexpr_constructible_
    {
      template<typename U, typename... UArgs>
      static constexpr auto init(tag_t<U, UArgs...>) ->
        decltype(void(U(UArgs()...)), 0)
      {
        return (void(U(UArgs()...)), 0);
      }

      template<typename U, int = init(tag<U, Args...>)>
      static std::true_type test(U*);
      static std::false_type test(void*);

      static constexpr bool value =
        decltype(test(static_cast<T*>(nullptr)))::value;
    };
  }

  template<typename T, typename... Args>
  inline constexpr bool is_constexpr_constructible_v =
    detail::is_constexpr_constructible_<T, std::decay_t<Args>...>::value;

  template<typename T, typename... Args>
  struct is_constexpr_constructible
    : std::integral_constant<bool, is_constexpr_constructible_v<T, Args...>> {};

  template<typename T, typename... Args>
  inline constexpr bool is_constexpr_nothrow_constructible_v =
    std::is_nothrow_constructible_v<T, Args...> && is_constexpr_constructible_v<T, Args...>;

  namespace detail
  {
    template<typename R, typename F, typename... Args>
    struct is_constexpr_invocable_
    {
      // not a perfect check
      // it tests only whether the return type and argument types are literal ones.
      template<typename U, typename... UArgs>
      static constexpr auto init(tag_t<R, U, UArgs...>)
        -> decltype(void(R()), void(UArgs()...), 0)
      {
        return (void(R()), void(UArgs()...), 0);
      }

      template<typename UR, int = init(tag<UR, F, Args...>)>
      static std::true_type test(UR*);

      static std::false_type test(void*);

      static constexpr bool value =
        decltype(test(static_cast<std::invoke_result_t<F, Args...>*>(nullptr)))::value;
    };
  }

  template<typename R, typename F, typename... Args>
  inline constexpr bool is_constexpr_invocable_r_v =
    detail::is_constexpr_invocable_<R, F, Args...>::value;

  template<typename R, typename F, typename... Args>
  struct is_constexpr_invocable_r
    : std::integral_constant<bool, is_constexpr_invocable_r_v<R, F, Args...>> {};

  template<typename R, typename T, typename... Args>
  inline constexpr bool is_constexpr_nothrow_invocable_r_v =
    std::is_nothrow_invocable_r_v<R, T, Args...> && is_constexpr_invocable_r_v<R, T, Args...>;

  //is_template;
  //Note: it's not going to work for templates which mix template value parameter type with template type parameter type
  template<typename>
  inline constexpr bool is_template_v = false;

  template<template<typename...> typename T, typename... As>
  inline constexpr bool is_template_v<T<As...>> = true;

  template<template<auto...> typename T, auto... As>
  inline constexpr bool is_template_v<T<As...>> = true;

  template<typename T>
  struct is_template : std::bool_constant<is_template_v<T>>
  {
  };

  //is_same_template; the types use the same template type
  //Note: it's not going to work for templates which mix template value parameter type with template type parameter type
  template<typename, typename>
  inline constexpr bool is_same_template_v = false;

  template<template<typename...> typename T, typename... As, typename... Bs>
  inline constexpr bool is_same_template_v<T<As...>, T<Bs...>> = true;

  template<template<auto...> typename T, auto... As, auto... Bs>
  inline constexpr bool is_same_template_v<T<As...>, T<Bs...>> = true;

  template<typename A, typename B>
  struct is_same_template : std::bool_constant<is_same_template_v<A, B>>
  {
  };
}

#endif