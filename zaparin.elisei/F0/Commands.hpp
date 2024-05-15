#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include "Hash.hpp"

namespace zaparin
{
  void createDict(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);

  void addWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void getWordRate(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void removeWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void deleteWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void getAllWordsRate(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void getHighestRateWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void getLowestRateWord(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void getWordsWithRate(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void getThreeHighestRateWords(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);

  void mergeDicts(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void intersectDicts(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);
  void excluseDicts(std::map< std::string, zaparin::HashTable >& dicts, std::istream& in, std::ostream& out);

}

#endif
