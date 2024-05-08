#ifndef FORMATS_HPP
#define FORMATS_HPP

#include <istream>
#include <cstddef>
#include <complex>

namespace grechishnikov
{
  struct OctFormat
  {
    size_t& key;
  };
  std::istream& operator>>(std::istream& in, OctFormat&& key1);

  struct ComplexFormat
  {
    std::complex< double >& key;
  };
  std::istream& operator>>(std::istream& in, ComplexFormat&& key2);

  struct StringFormat
  {
    std::string& key;
  };
  std::istream& operator>>(std::istream& in, StringFormat&& kay3);

}

#endif
