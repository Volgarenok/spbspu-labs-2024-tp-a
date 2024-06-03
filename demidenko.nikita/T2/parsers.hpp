#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <complex>
#include <parserTemplate.hpp>
#include <string>
#include "keysEnum.hpp"

namespace demidenko
{
  using KeyI = detail::ParserI< KeysEnum& >;
  using ComplexI = detail::ParserI< std::complex< double >& >;
  using UnsignedLongLongI = detail::ParserI< unsigned long long& >;
  using StringI = detail::ParserI< std::string& >;
}

#endif
