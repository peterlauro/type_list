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
  using my_list_types = stdx::type_list<int, double, literal_type, char>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Insert, list_one_type_0)
  {
    using t1 = decltype(my_list_one_type::insert<0U, char>());
    static_assert(std::is_same_v<t1, stdx::type_list<char, int>>);

    using t2 = decltype(my_list_one_type::insert<0U, char, size_t>());
    static_assert(std::is_same_v<t2, stdx::type_list<char, size_t, int>>);
  }

  TEST(TypeList_Insert, list_one_type_1)
  {
    using t = decltype(my_list_one_type::split<1U>());
    static_assert(std::is_same_v<t, stdx::type_list<stdx::type_list<int>, stdx::type_list<>>>);
  }

  TEST(TypeList_Insert, list_two_types)
  {
    using t = decltype(my_list_two_types::split<1U>());
    static_assert(std::is_same_v<t, stdx::type_list<stdx::type_list<int>, stdx::type_list<double>>>);
  }

  TEST(TypeList_Insert, list_four_types)
  {
    using t0 = decltype(my_list_types::insert<0U>(int{}));
    static_assert(std::is_same_v<t0, stdx::type_list<int, int, double, literal_type, char>>);

    using t1 = decltype(my_list_types::insert<1U>(int{}));
    static_assert(std::is_same_v<t1, stdx::type_list<int, int, double, literal_type, char>>);

    using t2 = decltype(my_list_types::insert<2U>(int{}));
    static_assert(std::is_same_v<t2, stdx::type_list<int, double, int, literal_type, char>>);

    using t3 = decltype(my_list_types::insert<3U>(int{}));
    static_assert(std::is_same_v<t3, stdx::type_list<int, double, literal_type, int, char>>);

    using t4 = decltype(my_list_types::insert<4U>(int{}));
    static_assert(std::is_same_v<t4, stdx::type_list<int, double, literal_type, char, int>>);
  }

  TEST(TypeList_Insert, empty_list_type)
  {
    using t0 = decltype(my_empty_list_type::insert<0U>(5));
    static_assert(std::is_same_v<t0, stdx::type_list<int>>);

    using t1 = decltype(my_empty_list_type::insert<0U, int>());
    static_assert(std::is_same_v<t1, stdx::type_list<int>>);
  }
}
