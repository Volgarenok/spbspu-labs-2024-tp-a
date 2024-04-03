#ifndef PARSER_TEMPLATE_HPP
#define PARSER_TEMPLATE_HPP

#include <istream>
#include "streamGuard.hpp"

namespace demidenko
{
  namespace detail
  {
    template < typename T >
    struct ParserI
    {
      T data;
      void parse(std::istream& in);
    };

    template < typename T >
    std::istream& operator>>(std::istream& in, ParserI< T >&& parser)
    {
      StreamGuard guard(in);
      in >> std::noskipws;
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      parser.parse(in);
      return in;
    }
  }
}

#endif
