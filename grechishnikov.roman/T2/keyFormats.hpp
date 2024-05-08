#ifndef KEY_FORMATS_HPP
#define KEY_FORMATS_HPP

#include <istream>
#include <cstddef>
#include <complex>

namespace grechishnikov
{
  struct Key1Format
  {
    size_t& key;
  };
  std::istream& operator>>(std::istream& in, Key1Format&& key1);

  struct Key2Format
  {
    std::complex< double >& key;
  };
  std::istream& operator>>(std::istream& in, Key2Format&& key2);

  struct Key3Format
  {
    std::string& key;
  };
  std::istream& operator>>(std::istream& in, Key3Format&& kay3);

}

#endif
