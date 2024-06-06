#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>
#include <complex>

namespace ishmuratov
{
  struct Delimeter
  {
    const char expected;
  };

  struct DelimeterUll
  {
    size_t & ref;
  };

  struct DelimeterComplex
  {
    std::complex< double > & ref;
  };

  struct DelimeterString
  {
    std::string & ref;
  };

  std::istream & operator>>(std::istream & in, Delimeter && exp);
  std::istream & operator>>(std::istream & in, DelimeterUll && exp);
  std::istream & operator>>(std::istream & in, DelimeterComplex && exp);
  std::istream & operator>>(std::istream & in, DelimeterString && exp);
}

#endif
