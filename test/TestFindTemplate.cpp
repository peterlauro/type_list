#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  template<auto Value>
  struct literal_value_t
  {
    constexpr literal_value_t() = default;
  };

  using literal_v1 = literal_value_t<1>;
  using literal_v2 = literal_value_t<2>;
  using literal_v3 = literal_value_t<3>;
  using literal_v4 = literal_value_t<4>;

  using my_value_list_type = stdx::type_list<literal_v2, literal_v3, int, literal_v1, float, literal_v2>;

  template<typename T>
  struct literal_type_t
  {
    constexpr literal_type_t() = default;
  };

  using literal_t1 = literal_type_t<int>;
  using literal_t2 = literal_type_t<float>;
  using literal_t3 = literal_type_t<char>;
  using literal_t4 = literal_type_t<literal_value_t<25>>;

  using my_type_list_type = stdx::type_list<literal_t2, literal_t3, int, literal_t1, float, literal_t4>;

  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Find_Template, empty_list)
  {
    {
      using t = decltype(my_empty_list_type::find_template());
      static_assert(std::is_same_v<t, stdx::type_list<>>);
    }

    {
      using t = decltype(my_empty_list_type::find_template(literal_value_t<0>{}));
      static_assert(std::is_same_v<t, stdx::type_list<>>);
    }
  }

  TEST(TypeList_Find_Template, template_with_value_parameter_type)
  {
    {
      using t = decltype(my_value_list_type::find_template(literal_value_t<0>{}));
      static_assert(std::is_same_v<t, stdx::type_list<literal_v2, literal_v3, literal_v1, literal_v2>>);
    }
  }

  TEST(TypeList_Find_Template, template_with_type_parameter_type)
  {
    {
      using t = decltype(my_type_list_type::find_template(literal_type_t<int>{}));
      static_assert(std::is_same_v<t, stdx::type_list<literal_t2, literal_t3, literal_t1, literal_t4>>);
    }
  }
}
