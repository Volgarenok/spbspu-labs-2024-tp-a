#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "dictionary.hpp"

namespace chernikova
{
  using Commands =
    std::map< std::string, std::function< void(std::map< std::string, Dictionary >&, std::istream&) > >;

  Commands initializeCommands();
  bool doCommand(std::map< std::string, Dictionary >& dataBase);
  void readData(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void saveData(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void addDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void insertWord(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void forceInsertWords(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void forceInsertLine(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void deleteWord(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void print(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void editWord(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void clearDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void getNumberWords(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void merge(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void intersection(std::map< std::string, Dictionary >& dataBase, std::istream& input);
}

#endif
