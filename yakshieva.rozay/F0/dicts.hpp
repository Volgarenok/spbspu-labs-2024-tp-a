#ifndef DICTS_HPP
#define DICTS_HPP

#include <map>
#include <set>
#include <string>

namespace yakshieva
{
  using number_t = size_t;
  using num_set_t = std::set< number_t >;
  using word_t = std::map< std::string, num_set_t >;
  using tree_t = std::map< std::string, std::tuple< word_t, std::string, size_t > >;
  void outText(const std::string& text, size_t lastLineNum, std::ostream& out);
  void outDict(const word_t& dict, std::ostream& out);
  void outLink(const word_t::value_type& translation, std::ostream& out);
  void outNumList(const num_set_t& list, std::ostream& out);
  void fileDict(const word_t& dict, std::ofstream& file);
  void fileLink(const word_t::value_type& translation, std::ofstream& file);
  void fileNumList(const num_set_t& list, std::ofstream& file);
}

#endif
