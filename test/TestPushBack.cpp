#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  struct literal_type
  {
    constexpr literal_type() = default;
  };

  using list_type = stdx::type_list<int, double>;

  TEST(TypeList_PushBack, no_type)
  {
    using t = decltype(list_type::push_back());
    static_assert(std::is_same_v<t, list_type>);
  }

  TEST(TypeList_PushBack, one_type)
  {
    using t = decltype(list_type::push_back(2.4f));
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float>>);
  }

  TEST(TypeList_PushBack, one_type_template)
  {
    using t = decltype(list_type::push_back<float>());
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float>>);
  }

  TEST(TypeList_PushBack, two_types)
  {
    using t = decltype(list_type::push_back(float{}, literal_type{}));
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float, literal_type>>);
  }

  TEST(TypeList_PushBack, one_template_type_parameter)
  {
    using t = decltype(list_type::push_back<float>());
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float>>);
  }

  TEST(TypeList_PushBack, two_template_type_parameters)
  {
    using t = decltype(list_type::push_back<float, literal_type>());
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float, literal_type>>);
  }

  TEST(TypeList_PushBack, one_list_type)
  {
    using t = decltype(list_type::push_back(stdx::type_list<float>()));
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float>>);
  }

  TEST(TypeList_PushBack, mixed_types)
  {
    using t = decltype(list_type::push_back<stdx::type_list<float>, literal_type>());
    static_assert(std::is_same_v<t, stdx::type_list<int, double, float, literal_type>>);
  }
}
