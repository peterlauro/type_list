#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_list_one_type = stdx::type_list<int>;
  using my_list_three_types = stdx::type_list<int, double, char>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Reverse, list_one_type)
  {
    using t = decltype(my_list_one_type::reverse());
    static_assert(std::is_same_v<t, stdx::type_list<int>>);
  }

  TEST(TypeList_Reverse, list_three_types)
  {
    using t = decltype(my_list_three_types::reverse());
    static_assert(std::is_same_v<t, stdx::type_list<char, double,int>>);
  }

  TEST(TypeList_Reverse, empty_list_type)
  {
    using t = decltype(my_empty_list_type::reverse());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
