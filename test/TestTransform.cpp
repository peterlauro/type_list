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

  struct req
  {
    constexpr static kind k = kind::req;
  };

  struct rsp
  {
    constexpr static kind k = kind::rsp;
  };

  struct nfy
  {
    constexpr static kind k = kind::nfy;
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

  constexpr auto detector = [](auto x) constexpr -> decltype(auto){
    if constexpr (x.k == kind::req)
    {
      return req{};
    }
    else if constexpr (x.k == kind::rsp)
    {
      return rsp{};
    }
    else
    {
      return nfy{};
    }
  };

  TEST(TypeList_Transform, from_empty_list)
  {
    using t = decltype(my_empty_list_type::transform(detector));
    static_assert(std::is_same_v<t, stdx::type_list<>>);
  }

  TEST(TypeList_Transform, message_detector)
  {
    using t = decltype(messages::transform(detector));
    static_assert(std::is_same_v<t, stdx::type_list<req, req, req, rsp, rsp, rsp, nfy, nfy, nfy>>);
  }
}
