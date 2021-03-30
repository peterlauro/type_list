#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };


  using my_list_one_type = stdx::type_list<int>;
  using my_list_more_types = stdx::type_list<int, my_list_one_type, double, int, char, double>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Flatten, one_type)
  {
    using t = decltype(type_list<>::flatten(int{}));
    static_assert(std::is_same_v<t, stdx::type_list<int>>);
  }

  TEST(TypeList_Flatten, two_types)
  {
    using t = decltype(my_list_more_types::flatten(5, 5.5));
    static_assert(std::is_same_v<t, stdx::type_list<int, double>>);
  }

  TEST(TypeList_Flatten, list_more_types)
  {
    stdx::type_list<literal_type, uint8_t> list;
    using t = decltype(decltype(list)::flatten(my_list_more_types{}));
    static_assert(std::is_same_v<t, stdx::type_list<int, int, double, int, char, double>>);
  }

  TEST(TypeList_Flatten, combination_of_two_list_types)
  {
    using t = decltype(stdx::type_list<>::flatten(my_list_more_types{}, std::declval<my_list_one_type>()));
    static_assert(std::is_same_v<t, stdx::type_list<int, int, double, int, char, double, int>>);
  }

  TEST(TypeList_Flatten, combination_of_list_type_and_type)
  {
    using t = decltype(stdx::type_list<>::flatten(std::declval<literal_type>(), my_list_more_types{}));
    static_assert(std::is_same_v<t, stdx::type_list<literal_type, int, int, double, int, char, double>>);
  }

  TEST(TypeList_Flatten, empty_list_type)
  {
    using t = decltype(my_empty_list_type::flatten());
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }
}
