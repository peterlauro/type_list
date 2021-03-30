#include <type_list.h>
#include <gtest/gtest.h>

namespace stdx::test
{
  enum class kind
  {
    req = 0,
    rsp = 1,
    nfy = 2
  };

  template<kind K, int Id, int Value>
  struct literal
  {
    constexpr literal() = default;
    constexpr static kind k = K;
    constexpr static int id = Id;
    constexpr static int value = Value;
  };

  using req1 = literal<kind::req, 1, 15>;
  using req2 = literal<kind::req, 2, 16>;
  using req3 = literal<kind::req, 3, 17>;

  using rsp1 = literal<kind::rsp, 4, 15>;
  using rsp2 = literal<kind::rsp, 5, 16>;
  using rsp3 = literal<kind::rsp, 6, 17>;

  using nfy1 = literal<kind::nfy, 7, 15>;
  using nfy2 = literal<kind::nfy, 8, 16>;
  using nfy3 = literal<kind::nfy, 9, 17>;

  using messages = stdx::type_list<req1, req2, req3, rsp1, rsp2, rsp3, nfy1, nfy2, nfy3>;
  using my_empty_list_type = stdx::type_list<>;

  TEST(TypeList_Filter, no_predicate)
  {
    {
      using l = decltype(my_empty_list_type::filter());
      static_assert(std::is_same_v<l, stdx::type_list<>>);
    }

    {
      using l = decltype(messages::filter());
      static_assert(std::is_same_v<l, stdx::type_list<>>);
    }
  }

  constexpr auto withvalue = [](auto x) constexpr { return x.value == 17; };
  constexpr auto onlynfy = [](auto x) constexpr { return x.k == kind::nfy; };
  constexpr auto onlynfywithvalue = [](auto x) { return withvalue(x) && onlynfy(x); };

  TEST(TypeList_Filter, messages_filtered_by_value)
  {
    {
      using l = decltype(empty_type_list::filter(withvalue));
      static_assert(std::is_same_v<l, stdx::type_list<>>);
    }

    {
      using l = decltype(messages::filter(withvalue));
      static_assert(std::is_same_v<l, stdx::type_list<req3, rsp3, nfy3>>);
    }
  }

  TEST(TypeList_Filter, messages_with_by_value_plus_by_kind)
  {
    {
      using l = decltype(empty_type_list::filter(withvalue, onlynfy));
      static_assert(std::is_same_v<l, stdx::type_list<>>);
    }

    {
      //disjunctive behaviour with types repetition (nfy3 satisfy both predicates)
      using l = decltype(messages::filter(withvalue, onlynfy));
      static_assert(std::is_same_v<l, stdx::type_list<req3, rsp3, nfy3, nfy1, nfy2, nfy3>>);
    }
  }

  TEST(TypeList_Filter, messages_with_value_and_nfy)
  {
    {
      using l = decltype(empty_type_list::filter(onlynfywithvalue));
      static_assert(std::is_same_v<l, stdx::type_list<>>);
    }

    {
      using l = decltype(messages::filter(onlynfywithvalue));
      static_assert(std::is_same_v<l, stdx::type_list<nfy3>>);
    }

    {
      using l = decltype(decltype(messages::filter(withvalue))::filter(onlynfy));
      static_assert(std::is_same_v<l, stdx::type_list<nfy3>>);
    }

    {
      constexpr auto messages_with_17 = messages::filter(withvalue);
      constexpr auto messages_with_17_only_nfy = decltype(messages_with_17)::filter(onlynfy);
      using messages_with_17_only_nfy_t = std::decay_t<decltype(messages_with_17_only_nfy)>;
      static_assert(std::is_same_v<messages_with_17_only_nfy_t, stdx::type_list<nfy3>>);
    }

    {
      constexpr auto messages_with_17 = messages().filter(withvalue);
      constexpr auto messages_with_17_only_nfy = messages_with_17.filter(onlynfy);
      using messages_with_17_only_nfy_t = std::decay_t<decltype(messages_with_17_only_nfy)>;
      static_assert(std::is_same_v<messages_with_17_only_nfy_t, stdx::type_list<nfy3>>);
    }
  }
}