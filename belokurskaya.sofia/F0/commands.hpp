#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>

#include "eng-rusDictionary.hpp"

namespace belokurskaya
{
  namespace cmd
  {
    void createDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void removeDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void add(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void remove(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void assign(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void removeWords(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void getIntersection(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void getDifference(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void clear(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void display(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in, std::ostream& out);
    void getTranslation(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream&, std::ostream& out);
    void countTranslations(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in, std::ostream& out);
    void help(std::ostream& out);
    void checkFile(std::istream& in, std::ostream& out);
  }
}

#endif
