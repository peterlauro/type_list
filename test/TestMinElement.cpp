#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_empty_list_type = stdx::type_list<>;

  constexpr auto smallestSizeType = [](auto t1, auto t2) constexpr {
    return sizeof(t1) < sizeof(t2);
  };

  constexpr auto smallestAlignmentType = [](auto t1, auto t2) constexpr {
    return alignof(decltype(t1)) < alignof(decltype(t2));
  };

  TEST(TypeList_Min_Element, empty_list_type)
  {
    constexpr auto idx = my_empty_list_type::min_element(smallestSizeType);
    static_assert(idx == my_empty_list_type::npos);
  }

  TEST(TypeList_Min_Element, list_with_one_element)
  {
    constexpr auto idx = stdx::type_list<int>::min_element(smallestSizeType);
    static_assert(idx == 0U);
  }

  TEST(TypeList_Min_Element, detect_smallestSizeType)
  {
    {
      using my_list_type = stdx::type_list<bool, std::uint16_t, std::uint32_t, std::uint8_t, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestSizeType);
      static_assert(idx == 0U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, bool, std::uint32_t, std::uint8_t, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestSizeType);
      static_assert(idx == 1U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, bool, std::uint8_t, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestSizeType);
      static_assert(idx == 2U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, bool, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestSizeType);
      static_assert(idx == 2U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, std::uint64_t, bool>;
      constexpr auto idx = my_list_type::min_element(smallestSizeType);
      static_assert(idx == 2U);
    }
  }

  TEST(TypeList_Min_Element, detect_smallestAlignmentType)
  {
    {
      using my_list_type = stdx::type_list<bool, std::uint16_t, std::uint32_t, std::uint8_t, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestAlignmentType);
      static_assert(idx == 0U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, bool, std::uint32_t, std::uint8_t, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestAlignmentType);
      static_assert(idx == 1U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, bool, std::uint8_t, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestAlignmentType);
      static_assert(idx == 2U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, bool, std::uint64_t>;
      constexpr auto idx = my_list_type::min_element(smallestAlignmentType);
      static_assert(idx == 2U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, std::uint64_t, bool>;
      constexpr auto idx = my_list_type::min_element(smallestAlignmentType);
      static_assert(idx == 2U);
    }
  }
}