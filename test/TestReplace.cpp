#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };

  using my_list_types = stdx::type_list<literal_type, double, literal_type, char, literal_type>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Replace, from_empty_list)
  {
    {
      using t = decltype(my_empty_list_type::replace<int, float>());
        static_assert(std::is_same_v<t, stdx::type_list<>>);
    }

    {
      using t = decltype(my_empty_list_type::replace(int{}, float{}));
      static_assert(std::is_same_v<t, stdx::type_list<>>);
    }
  }

  TEST(TypeList_Replace, literal_type_to_int)
  {
    using t = decltype(my_list_types::replace<literal_type, int>());
    static_assert(std::is_same_v<t, stdx::type_list<int, double, int, char, int>>);
  }

  TEST(TypeList_Replace, literal_type_to_literal_type)
  {
    using t = decltype(my_list_types::replace<literal_type, literal_type>());
    static_assert(std::is_same_v<t, my_list_types>);
  }

  TEST(TypeList_Replace, double_to_int)
  {
    using t = decltype(my_list_types::replace(double{}, int{}));
    static_assert(std::is_same_v<t, stdx::type_list<literal_type, int, literal_type, char, literal_type>>);
  }
}
