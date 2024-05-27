#ifndef DICT_FUNCTIONS
#define DICT_FUNCTIONS
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void extendDict(dict_t & dict, std::istream & in);
}

#endif

