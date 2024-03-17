#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <fstream>
#include <string>
#include <complex>

namespace nikitov
{
  struct DataStruct
  {
    bool operator<(const DataStruct& other) const;

    char key1;
    std::complex< double > key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& input, DataStruct& value);
  std::ostream& operator<<(std::ostream& output, const DataStruct& value);

  std::istream& operator>>(std::istream& input, std::string& line);

  void inputKey(DataStruct& value, size_t keyNum, std::istream& input);
}
#endif
