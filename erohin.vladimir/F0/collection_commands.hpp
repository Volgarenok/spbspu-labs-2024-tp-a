#ifndef COLLECTION_COMMANDS_HPP
#define COLLECTION_COMMANDS_HPP

#include <iostream>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>
#include <forward_list>
#include <iterator>
#include <functional>
#include "input_output_collection.hpp"
#include "dictionary_record.hpp"
#include "number_format.hpp"

namespace erohin
{
  using texts_source = std::map< std::string, std::string >;
  using record_pair = std::pair< std::string, size_t >;

  void addTextCommand(texts_source & text_context, std::istream & input, std::ostream &);
  void removeTextCommand(texts_source & text_context, std::istream & input, std::ostream &);
  void createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &);
  void removeDictCommand(collection & dict_context, std::istream & input, std::ostream &);
  void printCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat);
  void countCommand(const collection & dict_context, std::istream & input, std::ostream & output);
  void sortCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat);
  void findCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat);
  void topCommand(collection & dict_context, std::istream & input, std::ostream &);
  void bottomCommand(collection & dict_context, std::istream & input, std::ostream &);
  void differCommand(collection & dict_context, std::istream & input, std::ostream &);
  void uniteCommand(collection & dict_context, std::istream & input, std::ostream &);
  void intersectCommand(collection & dict_context, std::istream & input, std::ostream &);

  namespace detail
  {
    template< class T1, class T2 >
    std::pair< T2, T1 > invertPair(const std::pair< T1, T2 > & pair)
    {
      return std::make_pair(pair.second, pair.first);
    }

    template< class T1, class T2 >
    size_t getNumber(const std::pair< T1, T2 > & pair)
    {
      return std::get< size_t >(pair);
    }

    template< class Dict >
    size_t countTotalNumber(const Dict & dict)
    {
      std::forward_list< size_t > number_seq;
      using T1 = typename Dict::key_type;
      using T2 = typename Dict::mapped_type;
      std::transform(dict.cbegin(), dict.cend(), std::front_inserter(number_seq), getNumber< T1, T2 >);
      size_t total_number = std::accumulate(number_seq.cbegin(), number_seq.cend(), 0);
      return total_number;
    }

    template< class Dict, class DictIter >
    void insertNumRecords(Dict & dict, size_t count, DictIter begin, DictIter end)
    {
      size_t prev_num = 0;
      size_t current_count = 0;
      while (begin != end && current_count != count)
      {
        dict.insert(invertPair(*begin));
        if (begin->first != prev_num)
        {
          ++current_count;
          prev_num = begin->first;
        }
        ++begin;
      }
    }
  }
}

#endif
