#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_t1
  {
    constexpr literal_t1() = default;
  };

  struct literal_t2
  {
    constexpr literal_t2() = default;
  };

  using my_list_one_type = stdx::type_list<int>;
  using my_list_two_types = stdx::type_list<int, double>;
  using my_list_type = stdx::type_list<int, double, literal_t1, char, int, double, literal_t2>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Find_Last_Of, empty_list_type)
  {
    static_assert(my_empty_list_type::find_last_of<0U>(int{}) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_Last_Of, pos_out_of_range)
  {
    static_assert(my_list_two_types::find_last_of<2U>(int{}) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_Last_Of, list_two_types)
  {
    constexpr auto i = my_list_two_types::find_last_of<int>();
    EXPECT_EQ(i, 0U);
    static_assert(my_list_two_types::find_last_of<int>() == 0U);
    static_assert(my_list_two_types::find_last_of<int, my_list_two_types::size() - 1U>() == 0U);
    static_assert(my_list_two_types::find_last_of<double, my_list_two_types::size() - 1U>() == 1U);
    static_assert(my_list_two_types::find_last_of<double, my_list_two_types::size() - 1U>() == 1U);
    static_assert(my_list_two_types::find_last_of<char, my_list_two_types::size() - 1U>() == my_list_two_types::npos);
  }

  TEST(TypeList_Find_Last_Of, my_list_type)
  {
    constexpr auto i = my_list_type::find_last_of<int>();
    EXPECT_EQ(i, 4U);
    static_assert(my_list_type::find_last_of<int>() == 4U);
    static_assert(my_list_type::find_last_of<int, my_list_type::size() - 1U>() == 4U);
    static_assert(my_list_type::find_last_of<int, 3U>() == 0U);
    static_assert(my_list_type::find_last_of<double, my_list_type::size() - 1U>() == 5U);
    static_assert(my_list_type::find_last_of<double, 3U>() == 1U);
    static_assert(my_list_type::find_last_of<char, my_list_type::size() - 1U>() == 3U);


    constexpr auto j = my_list_type::find_last_of<my_list_type::size() - 1U>(stdx::type_list<literal_t1>{});
    int val = 0;
    if constexpr (j == 2U)
    {
      val = 10;
    }
    EXPECT_EQ(val, 10) << j;
    static_assert(my_list_type::find_last_of<my_list_type::size() - 1U>(stdx::type_list<int, literal_t1>{}) == 4U);
  }
}
