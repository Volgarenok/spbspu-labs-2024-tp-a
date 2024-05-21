#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <map>
#include <ostream>
#include <string>

namespace kravchenko
{
  using FrequencyDict = std::map< std::string, size_t >;
  using DictionaryMap = std::map< std::string, FrequencyDict >;

  void cmdScanText(std::istream& in, DictionaryMap& data);
}

#endif
