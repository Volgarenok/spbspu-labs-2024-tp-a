#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "commands.hpp"

namespace zaparin
{
  size_t getNumOfWords(Dict& dict);

  std::string filter(std::string word);
  bool loadFile(Dict& dict, std::string& filename);

  bool contains(Dict& dict, std::pair< const std::string, size_t >& elem);
  bool not_contains(Dict& dict, std::pair< const std::string, size_t >& elem);

  bool compare(const std::pair< const std::string, size_t >& elem1, const std::pair< const std::string, size_t >& elem2);

  void saveDict(Dict& dict, std::ostream& out);
  void loadDict(Dict& dict, std::istream& in);
}

#endif

