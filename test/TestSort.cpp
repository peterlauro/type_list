#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  template <int val = 0>
  struct literal
  {
    constexpr literal() = default;
    constexpr static int value = val;
  };

  using literal_t0 = literal<0>;
  using literal_t1 = literal<1>;
  using literal_t2 = literal<2>;
  using literal_t3 = literal<3>;
  using literal_t4 = literal<4>;
  using literal_t5 = literal<5>;
  using literal_t6 = literal<6>;
  using literal_t7 = literal<7>;
  using literal_t8 = literal<8>;
  using literal_t9 = literal<9>;

  using my_descent_sorted_list_type = stdx::type_list<
    literal_t0,
    literal_t1,
    literal_t2,
    literal_t3,
    literal_t4,
    literal_t5,
    literal_t6,
    literal_t7,
    literal_t8,
    literal_t9
  >;

  using my_ascent_sorted_list_type = stdx::type_list<
    literal_t9,
    literal_t8,
    literal_t7,
    literal_t6,
    literal_t5,
    literal_t4,
    literal_t3,
    literal_t2,
    literal_t1,
    literal_t0
  >;

  using my_list_type = stdx::type_list<
    literal_t8,
    literal_t6,
    literal_t9,
    literal_t4,
    literal_t7,
    literal_t5,
    literal_t3,
    literal_t0,
    literal_t2,
    literal_t1
  >;

  using my_empty_list_type = stdx::type_list<>;

  constexpr auto descent_comparer =
    [](auto tx, auto ty) -> decltype(tx.value - ty.value){return tx.value - ty.value; };

  constexpr auto ascent_comparer =
    [](auto tx, auto ty) -> decltype(ty.value - tx.value) {return ty.value - tx.value; };

  TEST(TypeList_Sort, empty_list_type)
  {
    {
      using l = decltype(my_empty_list_type::sort(descent_comparer));
      static_assert(std::is_same_v<l, my_empty_list_type>);
    }

    {
      using l = decltype(my_empty_list_type::sort(ascent_comparer));
      static_assert(std::is_same_v<l, my_empty_list_type>);
    }
  }

  TEST(TypeList_Sort, descent_comparer)
  {
    {
      using list = decltype(my_descent_sorted_list_type::sort(descent_comparer));
      static_assert(std::is_same_v<list, my_descent_sorted_list_type>);
      int val = 0;
      if constexpr (std::is_same_v<list, my_descent_sorted_list_type>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using list = decltype(my_ascent_sorted_list_type::sort(descent_comparer));
      static_assert(std::is_same_v<list, my_descent_sorted_list_type>);
      int val = 0;
      if constexpr (std::is_same_v<list, my_descent_sorted_list_type>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using list = decltype(my_list_type::sort(descent_comparer));
      static_assert(std::is_same_v<list, my_descent_sorted_list_type>);
      int val = 0;
      if constexpr (std::is_same_v<list, my_descent_sorted_list_type>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }
  }

  TEST(TypeList_Sort, ascent_comparer)
  {
    {
      using list = decltype(my_descent_sorted_list_type::sort(ascent_comparer));
      static_assert(std::is_same_v<list, my_ascent_sorted_list_type>);
      int val = 0;
      if constexpr (std::is_same_v<list, my_ascent_sorted_list_type>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using list = decltype(my_ascent_sorted_list_type::sort(ascent_comparer));
      static_assert(std::is_same_v<list, my_ascent_sorted_list_type>);
      int val = 0;
      if constexpr (std::is_same_v<list, my_ascent_sorted_list_type>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }

    {
      using list = decltype(my_list_type::sort(ascent_comparer));
      static_assert(std::is_same_v<list, my_ascent_sorted_list_type>);
      int val = 0;
      if constexpr (std::is_same_v<list, my_ascent_sorted_list_type>)
      {
        ++val;
      }
      EXPECT_EQ(val, 1);
    }
  }
}