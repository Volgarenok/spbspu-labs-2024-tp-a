#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>

#include "dictionary.hpp"

namespace kornienko
{
  void help(std::ostream & out);
  using mapDict = std::map< std::string, Dictionary >;
  void createDictionary(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void deleteDictionary(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void addWord(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void deleteWord(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void addTranslation(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void output(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void merge(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void intersect(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void difference(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void limit(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void getTranslation(std::istream & in, std::ostream & out, mapDict & dictionaries);
  void notTranslated(std::istream & in, std::ostream & out, mapDict & dictionaries);
}

#endif
