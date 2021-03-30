#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_list_one_type = stdx::type_list<int>;
  using my_list_more_types = stdx::type_list<int, double, int, char, double>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Unique, list_one_type)
  {
    using t = decltype(my_list_one_type::unique());
    static_assert(std::is_same_v<t, stdx::type_list<int>>);
  }

  TEST(TypeList_Unique, list_more_types)
  {
    using t = decltype(my_list_more_types::unique());
    static_assert(std::is_same_v<t, stdx::type_list<int, double, char>>);
  }

  TEST(TypeList_Unique, empty_list_type)
  {
    using t = decltype(my_empty_list_type::unique());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
