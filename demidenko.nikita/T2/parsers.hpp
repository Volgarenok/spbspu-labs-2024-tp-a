#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <complex>
#include <string>
#include "keysEnum.hpp"
#include "parserTemplate.hpp"

namespace demidenko
{
  using DelimeterI = detail::ParserI< const char* >;
  using KeyI = detail::ParserI< KeysEnum& >;
  using ComplexI = detail::ParserI< std::complex< double >& >;
  using UnsignedLongLongI = detail::ParserI< unsigned long long& >;
  using StringI = detail::ParserI< std::string& >;
}

#endif
