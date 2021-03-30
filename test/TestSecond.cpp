#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_empty_list_type = stdx::type_list<>;
  using my_list_one_type = stdx::type_list<int>;
  using my_list_three_types = stdx::type_list<int, double, char>;
  using my_list_combined_type = stdx::type_list<int, my_list_three_types>;

  TEST(TypeList_Second, list_one_type)
  {
    using t = decltype(my_list_one_type::second());
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }

  TEST(TypeList_Second, list_three_types)
  {
    using t = decltype(my_list_three_types::second());
    static_assert(std::is_same_v<t, double>);
  }

  TEST(TypeList_Second, empty_list_type)
  {
    using t = decltype(my_empty_list_type::second());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }

  TEST(TypeList_Second, combined_list_type)
  {
    using t = decltype(my_list_combined_type::second());
    static_assert(std::is_same_v<t, my_list_three_types>);
  }
}
