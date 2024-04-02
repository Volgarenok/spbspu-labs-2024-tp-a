#ifndef KEY_DELIMITERS_HPP
#define KEY_DELIMITERS_HPP

#include <istream>
#include <cstddef>
#include <complex>

namespace grechishnikov
{
  struct Key1_Delimiter
  {
    Key1_Delimiter(size_t& val);
    size_t& key;
  };
  std::istream& operator>>(std::istream& in, Key1_Delimiter&& key1);

  struct Key2_Delimiter
  {
    Key2_Delimiter(std::complex< double >& val);
    std::complex< double >& key;
  };
  std::istream& operator>>(std::istream& in, Key2_Delimiter&& key2);

  struct Key3_Delimiter
  {
    Key3_Delimiter(std::string& val);
    std::string& key;
  };
  std::istream& operator>>(std::istream& in, Key3_Delimiter&& kay3);

}

#endif
