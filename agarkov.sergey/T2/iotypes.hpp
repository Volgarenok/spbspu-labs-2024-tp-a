#ifndef IOTYPES_HPP
#define IOTYPES_HPP

#include <complex>
#include <string>

namespace agarkov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct CharIO
  {
    char& num;
  };

  struct ComplexIO
  {
    std::complex< double >& cmp;
  };

  struct StringIO
  {
    std::string& str;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}


#endif
