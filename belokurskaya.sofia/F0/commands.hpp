#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "eng-rusDictionary.hpp"

namespace belokurskaya
{
  namespace cmd
  {
    void createDict(std::vector< EngRusDict >& vector, std::istream& in);
    void removeDict(std::vector< EngRusDict >& vector, std::istream& in);
    void add(std::vector< EngRusDict >& vector, std::istream& in);
    void remove(std::vector< EngRusDict >& vector, std::istream& in);
    void addWords(std::vector< EngRusDict >& vector, std::istream& in);
    void removeWords(std::vector< EngRusDict >& vector, std::istream& in);
    void getIntersection(std::vector< EngRusDict >& vector, std::istream& in);
    void getDifference(std::vector< EngRusDict >& vector, std::istream& in);
    void clear(std::vector< EngRusDict >& vector, std::istream& in);
    void display(std::vector< EngRusDict >& vector, std::istream& in, std::ostream& out);
    void getTranslation(std::vector< EngRusDict >& vector, std::istream& in, std::ostream& out);

    namespace subcmd
    {
      bool containsEngRusDict(std::vector< EngRusDict >& vector, std::string name);
      size_t findIndexDict(std::vector< EngRusDict >& vector, std::string name);
    }
  }
}

#endif
