#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <unordered_map>

namespace kartamyshev
{
  using FrequencyDictionary = std::unordered_map< std::string, std::size_t >;
  using DictionarySet = std::unordered_map< std::string, FrequencyDictionary >;

  void help(std::ostream& out);
  void create(DictionarySet& set, std::istream& in);
  void insert(DictionarySet& collection, std::istream& in);
  void fill_in(DictionarySet& set, std::istream& in);
  void list_information(DictionarySet& set, std::istream& in, std::ostream& out);
  void search(DictionarySet& set, std::istream& in, std::ostream& out);
  void delete_dictionary(DictionarySet& set, std::istream& in);
  void merge(DictionarySet& set, std::istream& in);
  void get_merge(DictionarySet& set, std::istream& in);
  void list_popular(DictionarySet& set, std::istream& in, std::ostream& out);
  void get_intersection(DictionarySet& set, std::istream& in);
  void list_rare(DictionarySet& set, std::istream& in, std::ostream& out);
  void clear(DictionarySet& set, std::istream& in);
  void list_range_words(DictionarySet& set, std::istream& in, std::ostream& out);

}
#endif COMMANDS_H
