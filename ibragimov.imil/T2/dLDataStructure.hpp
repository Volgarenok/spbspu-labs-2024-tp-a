#ifndef DBL_LIT_DATA_STRUCTURE_HPP
#define DBL_LIT_DATA_STRUCTURE_HPP

#include "dataStructure.hpp"
#include <iostream>
#include <string>

namespace ibragimov
{
  struct DLDataStructure: public DataStructure
  {
  public:
    DLDataStructure();
    DLDataStructure(const DLDataStructure&);
    DLDataStructure(DLDataStructure&&);
    DLDataStructure(double, double, std::string);
    ~DLDataStructure();
    DLDataStructure& operator=(const DLDataStructure&);
    DLDataStructure& operator=(DLDataStructure&&);

  private:
    double key1_;
    double key2_;
    std::string key3_;
  };
  std::istream& operator>>(std::istream&, const DLDataStructure&);
  std::ostream& operator<<(std::ostream&, DLDataStructure&);
}  

#endif
