#ifndef READ_DICTIONARY_HPP
#define READ_DICTIONARY_HPP

#include <fstream>
#include <sstream>
#include <iterator>
#include <unordered_map>

#include "eng-rusDictionary.hpp"

namespace belokurskaya
{
  std::unordered_map< std::string, EngRusDict > ReadEngRusDictFromFile(const std::string& pathToFile);
}

#endif
