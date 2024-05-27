#ifndef DICT_FUNCTIONS
#define DICT_FUNCTIONS
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void extendDict(dict_t & dict, std::istream & in);
  bool countComparator(const std::pair< std::string, size_t > lhs, const std::pair< std::string, size_t > rhs);
  bool isContains(const dict_t & dict, const std::pair< std::string, size_t > & item);
}

#endif

