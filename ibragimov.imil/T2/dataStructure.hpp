#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include <complex>
#include <iostream>
#include <string>

namespace ibragimov
{
  struct DataStructure
  {
  public:
    double key1_;
    std::complex<double> key2_;
    std::string key3_;

    DataStructure(const double&, const std::complex<double>&, const std::string&);

  private:
  };
  std::istream& operator>>(std::istream&, DataStructure&);
  std::ostream& operator<<(std::ostream&, const DataStructure&);
}

#endif
