#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>

namespace chernikova
{
  class Dictionary
  {
  public:
    void insert(const std::string& word, const std::set< std::string >& translations);
  private:
    using map = std::unordered_map <std::string, std::set<std::string>>;
    map data_;
    static void printSet(std::ostream& output, const std::set < std::string >& set);
  };

}

#endif
