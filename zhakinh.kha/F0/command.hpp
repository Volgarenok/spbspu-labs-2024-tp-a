#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <ostream>
#include <istream>
#include <map>
#include "dictionary.hpp"

namespace zhakha
{
  using DictionaryMap = std::map<std::string, Dictionary>;
  using DictionaryIterator = DictionaryMap::iterator;

  void input(std::istream& in, DictionaryMap& dicts);
  void print(std::istream& in, const DictionaryMap& dicts);
  void topFreq(std::istream& in, std::ostream& out, const DictionaryMap& dicts);

  DictionaryIterator addDict(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator cmdChange(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator makeDict(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator intersect(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator unionD(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator uniqueD(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator addDtoD(std::istream& in, DictionaryMap& dicts);
  DictionaryIterator subD(std::istream& in, DictionaryMap& dicts);

}

#endif // !COMMAND_HPP
