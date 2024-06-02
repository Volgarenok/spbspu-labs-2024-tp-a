#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <utility>
#include <istream>

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

  template< typename First, typename Second >
  std::istream& readKeyAndValue(std::istream& in, std::pair< First, Second >& pair)
  {
    return in >> pair.first >> pair.second;
  }

  template< typename First, typename Second >
  std::istream& readKey(std::istream& in, std::pair< First, Second >& pair)
  {
    return in >> pair.first;
  }

  template< typename First, typename Second >
  std::istream& readValue(std::istream& in, std::pair< First, Second >& pair)
  {
    return in >> pair.second;
  }
}

#endif
