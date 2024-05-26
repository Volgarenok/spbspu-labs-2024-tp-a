#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>

namespace kuznetsov
{
  using frequency_dictionary = std::map< std::string, size_t >;
  void command_add_word(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_delete_word(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_output(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_create_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_delete_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_search_in_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_search_in_all_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_show_dictionary(std::map< std::string, frequency_dictionary >& data, std::ostream& out);
  void command_add_words_from_file(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_merge(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
}

#endif
