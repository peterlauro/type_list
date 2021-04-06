#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  using my_empty_list_type = stdx::type_list<>;

  constexpr auto largestSizeType = [](auto t1, auto t2) constexpr {
    return sizeof(t1) < sizeof(t2);
  };

  constexpr auto largestAlignmentType = [](auto t1, auto t2) constexpr {
    return alignof(decltype(t1)) < alignof(decltype(t2));
  };

  TEST(TypeList_Max_Element, empty_list_type)
  {
    constexpr auto idx = my_empty_list_type::max_element(largestSizeType);
    static_assert(idx == my_empty_list_type::npos);
  }

  TEST(TypeList_Max_Element, list_with_one_element)
  {
    constexpr auto idx = stdx::type_list<int>::max_element(largestSizeType);
    static_assert(idx == 0U);
  }

  TEST(TypeList_Max_Element, detect_largestSizeType)
  {
    {
      using my_list_type = stdx::type_list<std::uint64_t, std::uint16_t, std::uint32_t, std::uint8_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestSizeType);
      static_assert(idx == 0U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint64_t, std::uint32_t, std::uint8_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestSizeType);
      static_assert(idx == 1U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint64_t, std::uint8_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestSizeType);
      static_assert(idx == 2U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, std::uint64_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestSizeType);
      static_assert(idx == 3U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, bool, std::uint64_t>;
      constexpr auto idx = my_list_type::max_element(largestSizeType);
      static_assert(idx == 4U);
    }
  }

  TEST(TypeList_Max_Element, detect_largestAlignmentType)
  {
    {
      using my_list_type = stdx::type_list<std::uint64_t, std::uint16_t, std::uint32_t, std::uint8_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestAlignmentType);
      static_assert(idx == 0U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint64_t, std::uint32_t, std::uint8_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestAlignmentType);
      static_assert(idx == 1U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint64_t, std::uint8_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestAlignmentType);
      static_assert(idx == 2U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, std::uint64_t, bool>;
      constexpr auto idx = my_list_type::max_element(largestAlignmentType);
      static_assert(idx == 3U);
    }

    {
      using my_list_type = stdx::type_list<std::uint16_t, std::uint32_t, std::uint8_t, bool, std::uint64_t>;
      constexpr auto idx = my_list_type::max_element(largestAlignmentType);
      static_assert(idx == 4U);
    }
  }
}