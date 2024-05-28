#ifndef CLA_HPP
#define CLA_HPP
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void printHelp(std::ostream & out);
  void checkDictFile(char * argv[], std::ostream & out);
  void readDict(const std::string & fileName, std::string & dictName, dict_t & dict);
}

#endif

