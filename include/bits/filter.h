#ifndef STDX_BITS_FILTER_H
#define STDX_BITS_FILTER_H

namespace stdx::detail
{
  template<typename List>
  struct filter_mixin
  {
    static constexpr auto filter()
    {
      return List::create_empty();
    }

    // when more predicates are provided, the filter selects types
    // based on each predicates from the List type; if there is a type in the List
    // which satisfy x-predicates, the type will be listed x-times in the result List
    // have a look at Test example TestFilter.
    template<typename... UnaryPredicates>
    static constexpr auto filter(UnaryPredicates... ps)
    {
      return List::create_empty().push_back(filter_impl(ps)...);
    }

  private:
    template<typename UnaryPredicate>
    static constexpr auto filter_impl(UnaryPredicate p)
    {
      if constexpr (List::empty())
      {
        return List::create_empty();
      }
      else if constexpr (p(List::front()))
      {
        return List::create_empty().push_back(List::front(), List::pop_front().filter(p));
      }
      else
      {
        return List::create_empty().push_back(List::pop_front().filter(p));
      }
    }
  };
}

#endif