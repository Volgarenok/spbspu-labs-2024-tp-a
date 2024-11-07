#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <istream>
#include <string>
#include <complex>

namespace poleleyko
{
  struct DelimiterIO
  {
    char exp;
  };

  struct LabelIO
  {
    std::string & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  struct HexUllIO
  {
    unsigned long long & ref;
  };

  struct ComplexIO
  {
    std::complex< double > & ref;
  };


  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, LabelIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, HexUllIO && dest);
  std::istream & operator>>(std::istream & in, ComplexIO && dest);
}

#endif