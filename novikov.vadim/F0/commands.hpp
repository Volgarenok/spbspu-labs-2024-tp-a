#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <map>
#include <unordered_map>

namespace novikov
{
  using Dictionary = std::multimap< std::string, std::string >;
  using DictionariesStorage = std::unordered_map< std::string, Dictionary >;

  void insert(DictionariesStorage& storage, std::istream& in);
  void search(const DictionariesStorage& storage, std::istream& in, std::ostream& out);
  void searchKeys(const DictionariesStorage& storage, std::istream& in, std::ostream& out);
  void searchValues(const DictionariesStorage& storage, std::istream& in, std::ostream& out);
  void remove(DictionariesStorage& storage, std::istream& in);
  void removeKeys(DictionariesStorage& storage, std::istream& in);
  void removeValues(DictionariesStorage& storage, std::istream& in);

  void open(DictionariesStorage& storage, std::istream& in);
  void save(const DictionariesStorage& storage, std::istream& in);
  void close(DictionariesStorage& storage, std::istream& in);
  void print(const DictionariesStorage& storage, std::istream& in, std::ostream& out);
  void size(const DictionariesStorage& storage, std::istream& in, std::ostream& out);

  void merge(DictionariesStorage& storage, std::istream& in);
  void intersect(DictionariesStorage& storage, std::istream& in);
  void filter(DictionariesStorage& storage, std::istream& in);
  void invert(DictionariesStorage& storage, std::istream& in);
}

#endif
