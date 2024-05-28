#ifndef CLA_HPP
#define CLA_HPP
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void printHelp(std::ostream & out);
  void readDict(std::map< std::string, dict_t > & dicts, const char * argv[]);
}

#endif

