#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };

  using my_one_list_type = stdx::type_list<int>;
  using my_list_type = stdx::type_list<int, double, literal_type>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_PopBack, one_list_type)
  {
    using t = decltype(my_one_list_type::pop_back());
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }

  TEST(TypeList_PopBack, list_type)
  {
    using t = decltype(my_list_type::pop_back());
    static_assert(std::is_same_v<t, stdx::type_list<int, double>>);
  }

  TEST(TypeList_PopBack, empty_list_type)
  {
    using t = decltype(my_empty_list_type::pop_back());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
