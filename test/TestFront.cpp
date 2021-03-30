#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_list_one_type = stdx::type_list<int>;
  using my_list_two_types = stdx::type_list<int, double>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Front, list_one_type)
  {
    using t = decltype(my_list_one_type::front());
    static_assert(std::is_same_v<t, int>);
  }

  TEST(TypeList_Front, list_two_types)
  {
    using t = decltype(my_list_two_types::front());
    static_assert(std::is_same_v<t, int>);
  }

  TEST(TypeList_Front, empty_list_type)
  {
    using t = decltype(my_empty_list_type::front());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
