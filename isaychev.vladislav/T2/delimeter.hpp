#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iosfwd>
#include <complex>

namespace isaychev
{
  struct DataStruct;

  struct DelimChI
  {
    char expected;
  };

  struct DelimStrI
  {
    const char * exp;
  };

  struct LongLongI
  {
    long long & ref;
  };

  struct ComplexI
  {
    std::complex< double > & ref;
  };

  struct StringI
  {
    std::string & ref;
  };

  std::istream & operator>>(std::istream & in, DelimChI && sym);
  std::istream & operator>>(std::istream & in, DelimStrI && key);
  std::istream & operator>>(std::istream & in, LongLongI && dest);
  std::istream & operator>>(std::istream & in, ComplexI && dest);
  std::istream & operator>>(std::istream & in, StringI && dest);
}

#endif
