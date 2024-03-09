#ifndef PARSE_KEY_HPP
#define PARSE_KEY_HPP

#include <istream>
#include <string>
#include <complex>

namespace kravchenko
{
  void parseKey(std::istream& in, long long& value);
  void parseKey(std::istream& in, std::complex< double >& value);
}

#endif
