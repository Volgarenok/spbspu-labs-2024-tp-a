#ifndef OUTPUTDATA_HPP
#define OUTPUTDATA_HPP

#include <iosfwd>

namespace zhalilov
{
  struct DataStruct;
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
}

#endif
