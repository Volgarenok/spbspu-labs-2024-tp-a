#ifndef KEYS_HPP
#define KEYS_HPP

#include <complex>
#include <iostream>
#include <string>

namespace vorobieva 
{
  struct ComplexKey 
  {
    std::complex<double> & smth;
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
  std::ostream & operator<<(std::ostream & out, BinaryKey && key);
  std::istream & operator>>(std::istream & in, StringKey && key);

}

#endif
