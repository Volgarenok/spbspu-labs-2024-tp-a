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
    DataStructure();
    DataStructure(const DataStructure&);
    DataStructure(DataStructure&&);
    DataStructure(double, double, std::string);
    ~DataStructure();
    DataStructure& operator=(const DataStructure&);
    DataStructure& operator=(DataStructure&&);

  private:
    double key1_;
    std::complex<double> key2_;
    std::string key3_;
  };
  std::istream& operator>>(std::istream&, DataStructure&);
  std::ostream& operator<<(std::ostream&, const DataStructure&);
}

#endif
