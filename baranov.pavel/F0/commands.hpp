#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void createCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void clearCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void addWordsCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void printCountCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
  void printDictCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
  void printTopCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
  void joinCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void intersectCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void saveCmd(const std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void lsDictsCmd(const std::map< std::string, dict_t > & dicts, std::istream &, std::ostream & out);
}

#endif

