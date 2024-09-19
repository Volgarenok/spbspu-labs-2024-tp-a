#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dictionary.hpp"

namespace kozlova
{
  void read(std::map< std::string, Dictionary >& dictionaries, std::istream& in);
  void readPart(std::map< std::string, Dictionary >& dictionaries, std::istream& in);
  void findMaxFreq(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out);
  void combiningDictionary(std::map< std::string, Dictionary >& dictionaries, std::istream& in);
  void removeWords(std::map< std::string, Dictionary >& dictionaries, std::istream& in);
  void deleteDictionary(std::map< std::string, Dictionary >& dicts, std::istream& in);
  void printFreqWord(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out);
  void predecessor(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out);
  void printDictCmd(const std::map< std::string, Dictionary >& dicts, std::istream& in, std::ostream& out);
}

#endif
