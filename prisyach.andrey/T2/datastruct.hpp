#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <istream>
#include <ostream>
#include <string>

namespace prisyach
{
  struct DataStruct
  {
    double firstKey;
    unsigned long long secondKey;
    std::string thirdKey;
    bool operator<(const DataStruct &) const;
  };
  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif