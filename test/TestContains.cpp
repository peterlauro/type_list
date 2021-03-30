#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };

  using my_list_one_type = stdx::type_list<int>;
  using my_list_two_types = stdx::type_list<int, double>;
  using my_list_type = stdx::type_list<int, double, my_list_two_types, literal_type > ;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Contains, list_one_type)
  {
    EXPECT_TRUE(my_list_one_type::contains<int>());
    EXPECT_TRUE(my_list_one_type::contains(5));
  }

  TEST(TypeList_Contains, list_two_types)
  {
    EXPECT_TRUE(my_list_two_types::contains(5.4));
    EXPECT_TRUE(my_list_two_types::contains<double>());
  }

  TEST(TypeList_Contains, list_with_list_type)
  {
    EXPECT_TRUE(my_list_type::contains(my_list_two_types{}));
    EXPECT_TRUE(my_list_type::contains<my_list_two_types>());
  }
}
