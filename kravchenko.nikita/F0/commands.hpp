#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <utility>

namespace kravchenko
{
  using FrequencyDict = std::map< std::string, size_t >;
  using DictionaryMap = std::map< std::string, FrequencyDict >;

  void cmdScanText(std::istream& in, DictionaryMap& data);
  void cmdNew(std::istream& in, DictionaryMap& data);
  void cmdRemove(std::istream& in, DictionaryMap& data);
  void cmdList(std::ostream& out, const DictionaryMap& data);
  void cmdSave(std::istream& in, std::ostream& out, const DictionaryMap& data);
}

#endif
