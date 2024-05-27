#ifndef READ_DICTIONARY_HPP
#define READ_DICTIONARY_HPP

#include <fstream>
#include <sstream>

#include "eng-rusDictionary.hpp"

namespace belokurskaya
{
  std::vector< belokurskaya::EngRusDict > ReadEngRusDictFromFile(std::string pathToFile);
}

#endif
