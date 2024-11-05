 #ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <complex>

namespace agarkov
{
  struct DataStruct
  {
    char key1;
    std::complex< double > key2;
    std::string key3;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  std::istream& operator>>(std::istream& in, DataStruct& data);

  struct Comparator
  {
    bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
  };
}

#endif
