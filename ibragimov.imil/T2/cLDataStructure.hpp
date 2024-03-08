#ifndef CMP_LSP_DATA_STRUCTURE_HPP
#define CMP_LSP_DATA_STRUCTURE_HPP

#include "dataStructure.hpp"
#include <complex>
#include <iostream>
#include <string>

namespace ibragimov
{
  struct CLDataStructure: public DataStructure
  {
  public:
    CLDataStructure();
    CLDataStructure(const CLDataStructure&);
    CLDataStructure(CLDataStructure&&);
    CLDataStructure(double, double, std::string);
    ~CLDataStructure();
    CLDataStructure& operator=(const CLDataStructure&);
    CLDataStructure& operator=(CLDataStructure&&);

  private:
    std::complex<double> key1_;
    std::pair<long long, unsigned long long> key2_;
    std::string key3_;
  };
  std::istream& operator>>(std::istream&, const CLDataStructure&);
  std::ostream& operator<<(std::ostream&, CLDataStructure&);
} 

#endif
