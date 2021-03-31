#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal
  {
    constexpr literal() = default;
  };

  TEST(TypeList, class_template_argument_deduction)
  {
    {
      using my_type_list = stdx::type_list<int, double, literal>;
      stdx::type_list tl(int{}, double{}, literal{});
      static_assert(std::is_same_v<decltype(tl), my_type_list>);
      int val = 0;
      if constexpr (std::is_same_v<decltype(tl), my_type_list>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using my_type_list = stdx::type_list<int, float, char>;
      stdx::type_list tl(1, 0.5f, 'c');
      static_assert(std::is_same_v<decltype(tl), my_type_list>);
      int val = 0;
      if constexpr (std::is_same_v<decltype(tl), my_type_list>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using my_type_list = stdx::type_list<int, float, char>;
      int i = 5;
      float f = 2.0f;
      char c = 'f';
      stdx::type_list tl(i, f, c);
      static_assert(std::is_same_v<decltype(tl), my_type_list>);
      int val = 0;
      if constexpr (std::is_same_v<decltype(tl), my_type_list>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using my_type_list = stdx::type_list<>; //empty type list
      stdx::type_list tl;
      static_assert(std::is_same_v<decltype(tl), my_type_list>);
      int val = 0;
      if constexpr (std::is_same_v<decltype(tl), my_type_list>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }
  }
}
