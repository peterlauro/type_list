#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_t1
  {
    constexpr literal_t1() = default;
    constexpr static int value = 1;
  };

  struct literal_t2
  {
    constexpr literal_t2() = default;
    constexpr static int value = 2;
  };

  struct literal_t3
  {
    constexpr literal_t3() = default;
    constexpr static int value = 3;
  };

  struct literal_t4
  {
    constexpr literal_t4() = default;
    constexpr static int value = 4;
  };

  using my_list_type = stdx::type_list<literal_t2, literal_t3, literal_t1, literal_t4, literal_t2>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Find_If_Not, empty_list_type)
  {
    static_assert(my_empty_list_type::find_if_not<0U>([](auto x) {return true; }) == my_empty_list_type::npos);
    static_assert(my_empty_list_type::find_if_not([](auto x) {return true; }) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_If_Not, pos_out_of_range)
  {
    static_assert(my_list_type::find_if_not<my_list_type::size()>([](auto x) { return true; }) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_If_Not, find_value_1)
  {
    static constexpr auto searched_value = 1;
    constexpr auto predicate = [](auto x) constexpr {return decltype(x)::value == searched_value; };
    auto val = 0;
    if constexpr (my_list_type::find_if_not(predicate) == 0U)
    {
      val = 10;
    }
    EXPECT_EQ(val, 10);
    static_assert(my_list_type::find_if_not<1U>(predicate) == 1U);
    static_assert(my_list_type::find_if_not(predicate) == 0U);
  }
}