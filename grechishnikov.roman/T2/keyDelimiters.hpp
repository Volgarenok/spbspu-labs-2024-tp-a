#ifndef KEY_DELIMITERS_HPP
#define KEY_DELIMITERS_HPP

#include <istream>
#include <cstddef>
#include <complex>

namespace grechishnikov
{
  struct Key1Delimiter
  {
    size_t& key;
  };
  std::istream& operator>>(std::istream& in, Key1Delimiter&& key1);

  struct Key2Delimiter
  {
    std::complex< double >& key;
  };
  std::istream& operator>>(std::istream& in, Key2Delimiter&& key2);

  struct Key3Delimiter
  {
    std::string& key;
  };
  std::istream& operator>>(std::istream& in, Key3Delimiter&& kay3);

}

#endif
