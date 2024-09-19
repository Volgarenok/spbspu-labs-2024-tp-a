#ifndef IO_WORK_HPP
#define IO_WORK_HPP

#include <algorithm>
#include <limits>
#include <iostream>
#include <iterator>

namespace petrov
{
  template < class T >
  T& readFromStream(std::istream& in, T& dest)
  {
    while (!in.eof())
    {
      using isIt = std::istream_iterator< class T::value_type >;
      std::copy(isIt(in), isIt(), std::back_inserter(dest));
      if (in.fail())
      {
        in.clear();
        using numLim = std::numeric_limits< std::streamsize >;
        in.ignore(numLim::max(), '\n');
      }
    }
    return dest;
  }
}

#endif
