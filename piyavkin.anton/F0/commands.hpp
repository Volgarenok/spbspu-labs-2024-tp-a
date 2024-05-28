#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <istream>
#include <map>
#include "dictionary.hpp"

namespace piyavkin
{
  using tree_t = std::map< std::string, size_t >;
  using dic_t = std::map< std::string, tree_t >;
  using iterator = dic_t::iterator;
  void input(std::istream& in, dic_t& dicts);
  void print(std::istream& in, const dic_t& dicts);
  void topFreq(std::istream& in, std::ostream& out, const dic_t& dicts);
  iterator addDict(std::istream& in, dic_t& dicts);
  iterator cmdChange(std::istream& in, dic_t& dicts);
  iterator makeDict(std::istream& in, dic_t& dicts);
  iterator intersect(std::istream& in, dic_t& dicts);
  iterator unionD(std::istream& in, dic_t& dicts);
  iterator uniqueD(std::istream& in, dic_t& dicts);
  iterator addDtoD(std::istream& in, dic_t& dicts);
  iterator subD(std::istream& in, dic_t& dicts);
}
#endif
