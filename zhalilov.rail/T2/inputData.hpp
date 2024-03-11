#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iosfwd>

namespace zhalilov
{
  struct DataStruct;
  std::istream &operator>>(std::istream &in, DataStruct &data);
}

#endif