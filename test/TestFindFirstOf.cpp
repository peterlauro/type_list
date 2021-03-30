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
  using my_list_type = stdx::type_list<int, double, literal_t1, char, literal_t2>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Find_First_Of, empty_list_type)
  {
    static_assert(my_empty_list_type::find_first_of<0U>(int{}) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_First_Of, pos_out_of_range)
  {
    static_assert(my_list_two_types::find_first_of<2U>(int{}) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_First_Of, list_two_types)
  {
    static_assert(my_list_two_types::find_first_of<int>() == 0U);
    static_assert(my_list_two_types::find_first_of<int, 0U>() == 0U);
    static_assert(my_list_two_types::find_first_of<double, 0U>() == 1U);
    static_assert(my_list_two_types::find_first_of<double, 1U>() == 1U);
    static_assert(my_list_two_types::find_first_of<char, 0U>() == my_list_two_types::npos);
  }

  TEST(TypeList_Find_First_Of, my_list_type)
  {
    constexpr auto i = my_list_type::find_first_of<0U>(stdx::type_list<literal_t1>{});
    int val = 0;
    if constexpr (i == 2U)
    {
      val = 10;
    }
    EXPECT_EQ(val, 10) << i;
    static_assert(my_list_type::find_first_of<0U>(stdx::type_list<int, literal_t1>{}) == 0U);
  }
}
