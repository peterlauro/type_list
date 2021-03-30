#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_list_one_type = stdx::type_list<int>;
  using my_list_more_types = stdx::type_list<int, double, int, char, double>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_At, list_one_type_template)
  {
    using t = decltype(my_list_one_type::at<0>());
    static_assert(std::is_same_v<t, int>);
  }

  TEST(TypeList_At, my_list_move_types_template)
  {
    using t = decltype(my_list_more_types::at<3>());
    static_assert(std::is_same_v<t, char>);
  }

  TEST(TypeList_At, out_of_range_template)
  {
    using t = decltype(my_list_more_types::at<10>());
    static_assert(std::is_same_v<t, my_list_more_types::notype>);
  }

  TEST(TypeList_At, empty_list_type_template)
  {
    using t = decltype(my_empty_list_type::at<0>());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
