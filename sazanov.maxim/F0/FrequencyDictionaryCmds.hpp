#ifndef FREQUENCY_DICTIONARY_CMDS_HPP
#define FREQUENCY_DICTIONARY_CMDS_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

namespace sazanov
{
  using FrequencyDictionary = std::unordered_map< std::string, std::size_t >;
  using DictionaryCollection = std::unordered_map< std::string, FrequencyDictionary >;
  using Commands = std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > >;

  void insert(DictionaryCollection& dict, std::istream& in, std::ostream& out);
}

#endif
