#ifndef PARSERS_HPP
#define PARSERS_HPP

#include <complex>
#include <string>
#include "keysEnum.hpp"
#include "parserTemplate.hpp"

namespace demidenko
{
  using DelimeterI = ParserI< const char* >;
  using KeyI = ParserI< KeysEnum& >;
  using ComplexI = ParserI< std::complex< double >& >;
  using UnsignedLongLongI = ParserI< unsigned long long& >;
  using StringI = ParserI< std::string& >;
}

#endif
