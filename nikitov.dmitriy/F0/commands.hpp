#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include "dictionary.hpp"

namespace nikitov
{
  void printCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void addCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void editCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void deleteCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void findCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void translateCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void saveCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&);
}
#endif