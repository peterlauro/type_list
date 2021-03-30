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

  TEST(TypeList_PopFront, list_type)
  {
    using t = decltype(my_list_type::pop_front());
    static_assert(std::is_same_v<t, stdx::type_list<double, literal_type>>);
  }

  TEST(TypeList_PopFront, empty_list_type)
  {
    using t = decltype(my_empty_list_type::pop_front());
    static_assert(std::is_same_v<t, stdx::empty_type_list>);
  }
}
