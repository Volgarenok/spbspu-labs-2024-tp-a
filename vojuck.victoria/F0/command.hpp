#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <functional>

namespace vojuck
{
  using dict_t = std::map< std::string, size_t >;
  void printHelp(std::ostream & output);
  void increaseDict(dict_t & dict, std::istream & input);
  void makeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream &output);
  void saveDictToFile(std::ofstream & file, dict_t::const_iterator it, dict_t::const_iterator end);
  void loadCmd(std::map< std::string, dict_t > & dicts,std::istream & input, std::ostream & output);
  void deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void updateFreq(dict_t::iterator it, dict_t::iterator end, int totalWords);
  void addCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void removeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output);
  void wordFrequency(const std::map<std::string, dict_t>& dicts, std::istream & input, std::ostream& output);
  void printDictionaryFrequencies(const std::map<std::string, dict_t>& dicts,std::ifstream &input, std::ostream& output);
  void mergeDict(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
  void intersection(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
  void uniqueFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
  void minFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
  void maxFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
  void moreFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
  void lessFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output);
}

#endif
