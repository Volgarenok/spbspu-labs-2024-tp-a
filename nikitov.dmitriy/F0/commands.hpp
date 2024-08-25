#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "dictionary.hpp"

namespace nikitov
{
  void printHelp(std::ostream& output);

  void printDictCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void printAllCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void printNamesCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output);
  void findCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output,
    const std::string& parameter);
  void translateSentenceCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void translateFileCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void saveCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&);

  void createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void addCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter);
  void editCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter);
  void deleteCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter);
  void mergeCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
}
#endif
