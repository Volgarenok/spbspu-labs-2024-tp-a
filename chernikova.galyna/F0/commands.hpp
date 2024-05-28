#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <string>
#include "Dictionary.hpp"

namespace chernikova
{
  void doCommand(std::map< std::string, Dictionary >& dataBase, const std::string& command);
  void readData(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void saveData(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void addDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void insertWord(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void deleteWord(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void print(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void editWord(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void clearDictionary(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void getNumberWords(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void merge(std::map< std::string, Dictionary >& dataBase, std::istream& input);
  void intersection(std::map< std::string, Dictionary >& dataBase, std::istream& input);
}

#endif
