#ifndef LABEL_HPP
#define LABEL_HPP

#include <istream>
#include "streamGuard.hpp"

namespace ibragimov
{
  namespace formatters
  {
    template < class S >
    struct LabelI
    {
      const char* expectation;
    };
    template < class S >
    std::istream& operator>>(std::istream&, const LabelI< S >&&);

    template < class S >
    std::istream& operator>>(std::istream& in, const LabelI< S >&& value)
    {
      std::istream::sentry guard(in);
      if (!guard)
      {
        return in;
      }
      StreamGuard sGuard(in);
      char c = '\0';
      in >> std::noskipws;
      for (size_t i = 0; value.expectation[i] != '\0'; ++i)
      {
        in >> c;
        if ((in) && (!S::isSame(c, value.expectation[i])))
        {
          in.setstate(std::ios::failbit);
        }
      }
      return in;
    }
  }
}

#endif
