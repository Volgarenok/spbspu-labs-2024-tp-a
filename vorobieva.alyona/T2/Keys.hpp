#ifndef KEYS_HPP
#define KEYS_HPP

#include <iostream>
#include <complex>
#include <string>

namespace vorobieva
{
  struct ComplexKey
  {
    std::complex< double > & smth;
  };
  struct BinaryKey
  {
  unsigned long long & smth;
  };
  struct StringKey
  {
  std::string & smth;
  };
  std::istream & operator>>(std::istream & in, ComplexKey && key);
  std::istream & operator>>(std::istream & in, BinaryKey && key);
  std::istream & operator>>(std::istream & in, StringKey && key);
}

#endif
