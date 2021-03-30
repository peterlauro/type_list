#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };

  using my_list_type = stdx::type_list<int, double, literal_type>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Count, list_type)
  {
    EXPECT_EQ(my_list_type::count(), 3U);
  }

  TEST(TypeList_Count, empty_list_type)
  {
    EXPECT_EQ(my_empty_list_type::count(), 0U);
  }

  TEST(TypeList_Size, list_type)
  {
    EXPECT_EQ(my_list_type::size(), 3U);
  }

  TEST(TypeList_Size, empty_list_type)
  {
    EXPECT_EQ(my_empty_list_type::size(), 0U);
  }
}
