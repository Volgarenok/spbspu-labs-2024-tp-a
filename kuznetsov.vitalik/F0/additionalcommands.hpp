#ifndef ADDITIONAL_COMMANDS_HPP
#define ADDITIONAL_COMMANDS_HPP

#include <iostream>
#include <map>
#include <vector>

using data_word = std::pair< std::string, size_t >;
using frequency_dictionary = std::map< std::string, size_t >;

namespace kuznetsov
{
  bool check_word(std::string& word);
  bool sort_for_data_word(data_word& a, data_word& b);
  bool is_equal_for_data_word(data_word a, data_word b);
  std::vector< data_word > return_top_words(std::vector< frequency_dictionary >& dictionaries);
}

#endif
