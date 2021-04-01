#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  template<int Value>
  struct literal_type
  {
    constexpr literal_type() = default;
    constexpr static int value = Value;
  };

  using literal_t1 = literal_type<1>;
  using literal_t2 = literal_type<2>;
  using literal_t3 = literal_type<3>;
  using literal_t4 = literal_type<4>;

  using my_list_type = stdx::type_list<literal_t2, literal_t3, literal_t1, literal_t4, literal_t2>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Find_If, empty_list_type)
  {
    static_assert(my_empty_list_type::find_if<0U>([](auto x) {return true; }) == my_empty_list_type::npos);
    static_assert(my_empty_list_type::find_if([](auto x) {return true; }) == my_empty_list_type::npos);
  }

  TEST(TypeList_Find_If, pos_out_of_range)
  {
    static_assert(my_list_type::find_if<my_list_type::size()>([](auto x) { return true; }) == my_empty_list_type::npos);
  }

  constexpr auto predicate = [](auto x) constexpr -> bool {return x.value == 1; };

  TEST(TypeList_Find_If, find_value_1)
  {
    auto val = 0;
    if constexpr (my_list_type::find_if(predicate) == 2U)
    {
      val = 10;
    }
    EXPECT_EQ(val, 10);
    static_assert(my_list_type::find_if<1U>(predicate) == 2U);
    static_assert(my_list_type::find_if(predicate) == 2U);
  }
}