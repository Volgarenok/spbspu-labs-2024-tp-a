#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace kozlova
{
  using dictionary = std::map< std::string, size_t >;
  void read(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream&);
  void readPart(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream&);
  void findMaxFrequencyWord(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream&);
  void findFrequencyWordWith(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream&);
  void printFrequencyWord(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out);
  void deleteDictionary(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out);
  void deleteFrequencyWordWithPhrase(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out);
  void predecessor(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream&);
}

#endif
