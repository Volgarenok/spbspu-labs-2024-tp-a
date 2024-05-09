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

  void create(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void insert(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void getFrequency(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void erase(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void getMostFrequent(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void size(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void readText(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void save(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void print(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void readDict(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void merge(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void equal(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  void intersect(DictionaryCollection& collection, std::istream& in, std::ostream& out);
  bool copyOrIncreaseFrequency(FrequencyDictionary& result, const std::pair<std::string, std::size_t>& pair);
  bool intersectIfOtherDictContein(FrequencyDictionary& result, FrequencyDictionary & other, const std::pair<std::string, std::size_t>& pair);
}

#endif
