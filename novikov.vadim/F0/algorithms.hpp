#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <utility>

namespace novikov
{
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
