#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include <iostream>
#include <map>

namespace sivkov
{
  using map = std::map< std::string, std::map< std::string, std::string > >;
  void add_word(map& treeOfdic, std::istream& in);
  void add_translation(map& treeOfdic, std::istream& in);
  void create_dictionary(map& treeOfdic, std::istream& in);
  void remove_word(map& treeOfdic, std::istream& in);
  void list_words(const map& treeOfdic, std::istream& in, std::ostream& out);
  void count_words(const map& treeOfdic, std::istream& in, std::ostream& out);
  void search_words(const map& treeOfdic, std::istream& in, std::ostream& out);
  void delete_dictionary(map& treeOfdic, std::istream& in);
  void rename_dictionary(map& treeOfdic, std::istream& in);
  void merge_dictionaries(map& treeOfdic, std::istream& in);
  void repeating_words(const map& treeOfdic, std::istream& in, std::ostream& out);
  void save(const map& treeOfdic, const std::string& filename);
  void help(std::ostream& out);
}

#endif

