#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "dictionary.hpp"
namespace lopatina
{
  void doHelp(std::ostream & out);
  void createCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in);
  void printCmd(const std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out);
  void sortCmd(const std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out);
  void mostfrequentCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out);
  void deleteCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in);
  void compareCmd(const std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out);
  void combineCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in);
  void intersectCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in);
  void subtractCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in);
}

#endif
