#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_list_one_type = stdx::type_list<int>;
  using my_list_two_types = stdx::type_list<int, double>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Get, list_one_type)
  {
    using t0 = decltype(my_list_one_type::get<0U>());
    static_assert(std::is_same_v<t0, int>);

    using t1 = decltype(my_list_one_type::get<1U>());
    static_assert(std::is_same_v<t1, my_list_one_type::notype>);
  }

  TEST(TypeList_Get, list_two_types)
  {
    using t = decltype(my_list_two_types::get<0>());
    static_assert(std::is_same_v<t, int>);
  }

  TEST(TypeList_Get, empty_list_type)
  {
    using t = decltype(my_empty_list_type::get<0U>());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
