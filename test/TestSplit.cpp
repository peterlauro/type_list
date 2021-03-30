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

  TEST(TypeList_Split, list_one_type_0)
  {
    using t = decltype(my_list_one_type::split<0U>());
    static_assert(std::is_same_v<t, stdx::type_list<stdx::type_list<>, stdx::type_list<int>>>);
  }

  TEST(TypeList_Split, list_one_type_1)
  {
    using t = decltype(my_list_one_type::split<1U>());
    static_assert(std::is_same_v<t, stdx::type_list<stdx::type_list<int>, stdx::type_list<>>>);
  }

  TEST(TypeList_Split, list_two_types)
  {
    using t0 = decltype(my_list_two_types::split<0U>());
    static_assert(std::is_same_v<t0, stdx::type_list<stdx::type_list<>, stdx::type_list<int, double>>>);

    using t1 = decltype(my_list_two_types::split<1U>());
    static_assert(std::is_same_v<t1, stdx::type_list<stdx::type_list<int>, stdx::type_list<double>>>);

    using t2 = decltype(my_list_two_types::split<2U>());
    static_assert(std::is_same_v<t2, stdx::type_list<stdx::type_list<int, double>, stdx::type_list<>>>);

    using t3 = decltype(my_list_two_types::split<3U>());
    static_assert(std::is_same_v<t3, stdx::type_list<stdx::type_list<int, double>, stdx::type_list<>>>);
  }

  TEST(TypeList_Split, list_four_types)
  {
    using t0 = decltype(my_list_types::split<0U>());
    static_assert(std::is_same_v<t0, stdx::type_list<my_empty_list_type, my_list_types>>);

    using t1 = decltype(my_list_types::split<1U>());
    static_assert(std::is_same_v<t1, stdx::type_list<stdx::type_list<int>, stdx::type_list<double, literal_type, char>>>);

    using t2 = decltype(my_list_types::split<2U>());
    static_assert(std::is_same_v<t2, stdx::type_list<stdx::type_list<int, double>, stdx::type_list<literal_type, char>>>);

    using t3 = decltype(my_list_types::split<3U>());
    static_assert(std::is_same_v<t3, stdx::type_list<stdx::type_list<int, double, literal_type>, stdx::type_list<char>>>);

    using t4 = decltype(my_list_types::split<4U>());
    static_assert(std::is_same_v<t4, stdx::type_list<stdx::type_list<int, double, literal_type, char>, stdx::type_list<>>>);
  }

  TEST(TypeList_Split, empty_list_type)
  {
    using t0 = decltype(my_empty_list_type::split<0U>());
    static_assert(std::is_same_v<t0, stdx::type_list<stdx::type_list<>, stdx::type_list<>>>);

    using t1 = decltype(my_empty_list_type::split<1U>());
    static_assert(std::is_same_v<t1, stdx::type_list<stdx::type_list<>, stdx::type_list<>>>);
  }
}
