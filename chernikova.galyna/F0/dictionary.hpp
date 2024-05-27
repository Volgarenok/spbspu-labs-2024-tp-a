#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unordered_map>
#include <string>
#include <set>

namespace chernikova
{
  class Dictionary
  {
  private:
    using map = std::unordered_map <std::string, std::set<std::string>>;
    map data_;
  };

}

#endif

