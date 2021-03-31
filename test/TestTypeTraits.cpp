#include <type_traits.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct not_literal
  {
    not_literal(){}
    ~not_literal(){}
  };

  struct literal
  {
    constexpr literal() noexcept = default;
    constexpr literal(const int&, double) {}
    constexpr literal(int&&, double) {}
    constexpr literal(int&, double) {}
    literal(int, not_literal) {}
  };

  struct literal_derived : literal
  {
    constexpr literal_derived() noexcept(false)
    {}
  };

  struct non_literal_derived : not_literal
  {
    non_literal_derived() = default;
  };

  struct non_literal_derived_virtual : virtual literal
  {
  };

  TEST(TypeTraits_is_constexpr_default_constructible, literal_type)
  {
    static_assert(is_constexpr_default_constructible_v<literal>);
    int c = 0;
    if constexpr(is_constexpr_default_constructible_v<literal>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, nullptr_t_type)
  {
    static_assert(is_constexpr_default_constructible_v<std::nullptr_t>);
    int c = 0;
    if constexpr (is_constexpr_default_constructible_v<std::nullptr_t>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, int_type)
  {
    static_assert(is_constexpr_default_constructible_v<int>);
    int c = 0;
    if constexpr (is_constexpr_default_constructible_v<int>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, floating_type)
  {
    static_assert(is_constexpr_default_constructible_v<double>);
    int c = 0;
    if constexpr (is_constexpr_default_constructible_v<double>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, literal_derived_type)
  {
    static_assert(is_constexpr_default_constructible_v<literal_derived>);
    int c = 0;
    if constexpr (is_constexpr_default_constructible_v<literal_derived>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, non_literal_type)
  {
    static_assert(!is_constexpr_default_constructible_v<not_literal>);
    int c = 0;
    if constexpr (!is_constexpr_default_constructible_v<not_literal>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, non_literal_derived_type)
  {
    static_assert(!is_constexpr_default_constructible_v<non_literal_derived>);
    int c = 0;
    if constexpr (!is_constexpr_default_constructible_v<non_literal_derived>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_default_constructible, non_literal_derived_virtual_type)
  {
    static_assert(!is_constexpr_default_constructible_v<non_literal_derived_virtual>);
    int c = 0;
    if constexpr (!is_constexpr_default_constructible_v<non_literal_derived_virtual>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_nothrow_default_constructible_v, literal_type)
  {
    static_assert(is_constexpr_nothrow_default_constructible_v<literal>);
    int c = 0;
    if constexpr (is_constexpr_nothrow_default_constructible_v<literal>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_nothrow_default_constructible_v, literal_derived_type)
  {
    static_assert(!is_constexpr_nothrow_default_constructible_v<literal_derived>);
    int c = 0;
    if constexpr (!is_constexpr_nothrow_default_constructible_v<literal_derived>)
    {
      c = 10;
    }
    EXPECT_EQ(c, 10);
  }

  TEST(TypeTraits_is_constexpr_constructible, literal_type)
  {
    {
      static_assert(is_constexpr_constructible_v<literal, int&, double>);
      int c = 0;

      if constexpr (is_constexpr_constructible_v<literal, int&, double>)
      {
        c = 10;
      }
      EXPECT_EQ(c, 10);
    }

    {
      static_assert(is_constexpr_constructible_v<literal, int&&, double>);
      int c = 0;

      if constexpr (is_constexpr_constructible_v<literal, int&&, double>)
      {
        c = 10;
      }
      EXPECT_EQ(c, 10);
    }

    {
      static_assert(is_constexpr_constructible_v<literal, const int&, double>);
      int c = 0;

      if constexpr (is_constexpr_constructible_v<literal, const int&, double>)
      {
        c = 10;
      }
      EXPECT_EQ(c, 10);
    }
  }

  constexpr literal func()
  {
    return literal{};
  }

  constexpr literal func4(literal l)
  {
    return l;
  }

  not_literal func2()
  {
    return {};
  }

  literal func3(not_literal)
  {
    return {};
  }

  literal func5(literal, not_literal)
  {
    return {};
  }

  TEST(TypeTraits_is_constexpr_invocable, free_standing_function)
  {
    int v = 0;
    if constexpr (is_constexpr_invocable_r_v<not_literal, decltype(func2)>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<literal, decltype(func)>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<literal, decltype(func4), literal>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<literal, decltype(func3), not_literal>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<literal, decltype(func5), literal, not_literal>)
    {
      ++v;
    }
    EXPECT_EQ(v, 2);

    static_assert(is_constexpr_invocable_r_v<literal, decltype(func)>);
    static_assert(is_constexpr_invocable_r_v<literal, decltype(func4), literal>);
    static_assert(!is_constexpr_invocable_r_v<literal, decltype(func3), not_literal>);
    static_assert(!is_constexpr_invocable_r_v<not_literal, decltype(func2)>);
    static_assert(!is_constexpr_invocable_r_v<literal, decltype(func5), literal, not_literal>);
  }

  TEST(TypeTraits_is_constexpr_invocable, lambda)
  {
    constexpr auto lambda1 = [](int x) constexpr-> decltype(x < 5) {return x < 5; };
    constexpr auto lambda2 = []() constexpr { return true; };
    constexpr auto lambda3 = [](literal l) constexpr { return l; };
    constexpr auto lambda4 = [](literal l, not_literal) { return l; };
    int v = 0;
    if constexpr (is_constexpr_invocable_r_v<bool, decltype(lambda1), int>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<bool, decltype(lambda2)>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<literal, decltype(lambda3), literal>)
    {
      ++v;
    }
    if constexpr (is_constexpr_invocable_r_v<literal, decltype(lambda4), literal, not_literal>)
    {
      ++v;
    }
    EXPECT_EQ(v, 3);

    static_assert(is_constexpr_invocable_r_v<bool, decltype(lambda1), int>);
    static_assert(is_constexpr_invocable_r_v<bool, decltype(lambda2)>);
    static_assert(is_constexpr_invocable_r_v<literal, decltype(lambda3), literal>);
    static_assert(!is_constexpr_invocable_r_v<literal, decltype(lambda4), literal, not_literal>);
  }
}
