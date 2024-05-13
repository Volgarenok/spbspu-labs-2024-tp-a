#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <utility>

namespace novikov
{
  template< typename InputIt, typename OutputIt, typename UnaryPred, typename UnaryOp >
  OutputIt transformIf(InputIt begin_in, InputIt end_in, OutputIt begin_out, UnaryPred predicate, UnaryOp unary_op)
  {
    OutputIt itout = begin_out;
    for (InputIt itin = begin_in; itin != end_in; ++itin)
    {
      if (predicate(*itin))
      {
        *itout = unary_op(*itin);
        ++itout;
      }
    }
    return itout;
  }

  template< typename Container, typename UnaryPred >
  void eraseIf(Container& container, UnaryPred predicate)
  {
    for (auto it = container.begin(); it != container.end();)
    {
      if (predicate(*it))
      {
        it = container.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

  template< typename First, typename Second >
  std::pair< Second, First > invertPair(const std::pair< First, Second >& rhs)
  {
    return { rhs.second, rhs.first };
  }
}

#endif
