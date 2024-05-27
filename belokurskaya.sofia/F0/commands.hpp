#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>

#include "eng-rusDictionary.hpp"

namespace belokurskaya
{
  namespace cmd
  {
    void createDict(std::vector< EngRusDict >& vector, std::istream& in);
    void removeDict(std::vector< EngRusDict >& vector, std::istream& in);

    namespace subcmd
    {
      bool containsEngRusDict(std::vector< EngRusDict >& vector, std::string name);
      size_t findIndexDict(std::vector< EngRusDict >& vector, std::string name);
    }
  }
}

#endif
