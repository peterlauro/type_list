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
  using my_list_types = stdx::type_list<int, double, literal_type, char, int>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Remove, from_empty_list)
  {
    using t = decltype(my_empty_list_type::remove<int>());
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }

  TEST(TypeList_Remove, list_one_type__int)
  {
    using t = decltype(my_list_one_type::remove<int>());
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }

  TEST(TypeList_Remove, list_one_type__double)
  {
    using t = decltype(my_list_one_type::remove<double>());
    static_assert(std::is_same_v<t, stdx::type_list<int>>);
  }

  TEST(TypeList_Remove, list_one_type_1)
  {
    using t = decltype(my_list_one_type::remove(1));
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }

  TEST(TypeList_Remove, list_one_type_2)
  {
    using t = decltype(my_list_one_type::remove(2.5));
    static_assert(std::is_same_v<t, stdx::type_list<int>>);
  }

  TEST(TypeList_Remove, list_two_types)
  {
    using t = decltype(my_list_two_types::remove<int>());
    static_assert(std::is_same_v<t, stdx::type_list<double>>);
  }

  TEST(TypeList_Remove, list_four_types)
  {
    using t0 = decltype(my_list_types::remove<int>());
    static_assert(std::is_same_v<t0, stdx::type_list<double, literal_type, char>>);

    using t1 = decltype(my_list_types::remove<literal_type>());
    static_assert(std::is_same_v<t1, stdx::type_list<int, double, char, int>>);

    using t2 = decltype(my_list_types::remove('c'));
    static_assert(std::is_same_v<t2, stdx::type_list<int, double, literal_type, int>>);

    using t3 = decltype(my_list_types::remove());
    static_assert(std::is_same_v<t3, stdx::type_list<int, double, literal_type, char, int>>);
  }

  TEST(TypeList_Remove, empty_list_type)
  {
    using t0 = decltype(my_empty_list_type::remove());
    static_assert(std::is_same_v<t0, stdx::type_list<>>);
  }
}
