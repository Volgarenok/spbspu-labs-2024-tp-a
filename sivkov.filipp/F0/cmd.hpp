#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include <iostream>
#include <map>

namespace sivkov
{
  void add_word(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void add_translation(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void create_dictionary(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void remove_word(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void list_words(const std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void count_words(const std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void search_words(const std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out);
  void delete_dictionary(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void rename_dictionary(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void merge_dictionaries(std::map< std::string, std::map< std::string, std::string > >& treeOfdic, std::istream& in);
  void repeating_words(const std::map<std::string, std::map<std::string, std::string>>& treeOfdic, std::istream& in, std::ostream& out);
  void save(const std::map< std::string, std::map< std::string, std::string > >& treeOfdic, const std::string& filename);
  void help(std::ostream& out);
}

#endif

