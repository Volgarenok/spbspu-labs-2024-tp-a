#include "dataStruct.hpp"
#include <iostream>
#include <iomanip>

//std::istream & isaychev::operator>>(std::istream & in)
//{}

std::ostream & isaychev::operator<<(std::ostream & out, const DataStruct & obj)
{
  out << std::fixed;
  out << "(:key1 " << obj.key1;
  out << std::setprecision(1) << "ll:key2 #c(" << obj.key2.real();
  out << std::setprecision(1) << " " << obj.key2.imag() << ")";
  out << ":key3 \"" << obj.key3 << "\":)";
  return out;
}
