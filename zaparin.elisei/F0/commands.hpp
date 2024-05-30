#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <map>
#include <string>

namespace zaparin
{
  using Dict = std::unordered_map< std::string, size_t >;
  using Dicts = std::map< std::string, Dict >;

  void createDict(Dicts& dicts, std::istream& in, std::ostream& out);
  void addWord(Dicts& dicts, std::istream& in, std::ostream& out);
  void getWordRate(Dicts& dicts, std::istream& in, std::ostream& out);
  void removeWord(Dicts& dicts, std::istream& in, std::ostream& out);
  void deleteWord(Dicts& dicts, std::istream& in, std::ostream& out);
  void getAllWordsRate(Dicts& dicts, std::istream& in, std::ostream& out);
  void getHighestRateWord(Dicts& dicts, std::istream& in, std::ostream& out);
  void getLowestRateWord(Dicts& dicts, std::istream& in, std::ostream& out);
  void getWordsWithRate(Dicts& dicts, std::istream& in, std::ostream& out);

  void mergeDicts(Dicts& dicts, std::istream& in, std::ostream& out);
  void intersectDicts(Dicts& dicts, std::istream& in, std::ostream& out);
  void excluseDicts(Dicts& dicts, std::istream& in, std::ostream& out);

  void save(Dicts& dicts, std::istream& in, std::ostream& out);
  void load(Dicts& dicts, std::istream& in, std::ostream& out);

  void loadFile_cmd(Dicts& dicts, std::istream& in, std::ostream& out);
}

#endif

