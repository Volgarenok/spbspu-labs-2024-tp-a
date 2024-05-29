#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <complex>
#include <iostream>
#include <string>

namespace zagrivnyy
{
  struct DataStruct
  {
    char key1;                       ///< [CHR LIT] variant
    std::complex< double > key2;     ///< [CMP LSP] variant
    std::string key3;

    bool operator<(const DataStruct &src) const;
  };

  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);

  void parseInput(std::istream &in, char &data);
  void parseInput(std::istream &in, std::complex< double > &data);
  void parseInput(std::istream &in, std::string &data);
}

#endif
