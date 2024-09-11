#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include "predicates.hpp"
#include "customAlgorithms.hpp"

namespace novikov
{
  using Dictionary = std::multimap< std::string, std::string >;
  using DictionariesStorage = std::unordered_map< std::string, Dictionary >;

  void insert(DictionariesStorage& storage, std::istream& in);

  template< typename Strategy >
  void search(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
  {
    std::string dictionary;
    in >> dictionary;

    std::pair< std::string, std::string> temp;
    Strategy::input(in, temp);

    const auto& dict = storage.at(dictionary);
    auto pred = std::bind(Strategy::predicate, std::placeholders::_1, temp);
    std::vector< Word::words_pair_t > chosen;
    std::copy_if(dict.cbegin(), dict.cend(), std::back_inserter(chosen), pred);
    std::transform(chosen.cbegin(), chosen.cend(), std::ostream_iterator< Word >{ out, "\n" }, toWord);
  }

  template< typename Strategy >
  void remove(DictionariesStorage& storage, std::istream& in)
  {
    std::string dictionary;
    in >> dictionary;

    std::pair< std::string, std::string> temp;
    Strategy::input(in, temp);

    auto& dict = storage.at(dictionary);
    auto pred = std::bind(Strategy::predicate, std::placeholders::_1, temp);

    if (std::find_if(dict.cbegin(), dict.cend(), pred) == dict.cend())
    {
      throw std::invalid_argument("<INVALID_COMMAND>");
    }

    eraseIf(dict, pred);
  }

  void create(DictionariesStorage& storage, std::istream& in);
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
