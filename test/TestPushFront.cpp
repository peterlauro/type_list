#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };

  using list_type = stdx::type_list<int, double>;

  TEST(TypeList_PushFront, no_type)
  {
    using t = decltype(list_type::push_front());
    static_assert(std::is_same_v<t, list_type>);
  }

  TEST(TypeList_PushFront, one_type)
  {
    using t = decltype(list_type::push_front(2.4f));
    static_assert(std::is_same_v<t, stdx::type_list<float, int, double>>);
  }

  TEST(TypeList_PushFront, two_types)
  {
    using t = decltype(list_type::push_front(float{}, literal_type{}));
    static_assert(std::is_same_v<t, stdx::type_list<literal_type, float, int, double>>);
  }

  TEST(TypeList_PushFront, one_template_type_parameter)
  {
    using t = decltype(list_type::push_front<float>());
    static_assert(std::is_same_v<t, stdx::type_list<float, int, double>>);
  }

  TEST(TypeList_PushFront, two_template_type_parameters)
  {
    using t = decltype(list_type::push_front<float, literal_type>());
    static_assert(std::is_same_v<t, stdx::type_list<literal_type, float, int, double>>);
  }

  TEST(TypeList_PushFront, one_list_type)
  {
    using t = decltype(list_type::push_front(stdx::type_list<float>()));
    static_assert(std::is_same_v<t, stdx::type_list<float, int, double>>);
  }

  TEST(TypeList_PushFront, mixed_types)
  {
    using t = decltype(list_type::push_front<stdx::type_list<float>, literal_type>());
    static_assert(std::is_same_v<t, stdx::type_list<literal_type, float, int, double>>);
  }
}
