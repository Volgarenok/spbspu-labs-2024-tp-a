#ifndef COMLINEARG_HPP
#define COMLINEARG_HPP
#include <ostream>
#include <map>
#include "dictionary.hpp"

namespace piyavkin
{
  using dic_t = std::map< std::string, Dictionary >;
  void help(std::ostream& out);
  void check(std::istream& in, std::ostream& out, dic_t& dicts);
}
#endif
