#ifndef COMLINEARG_HPP
#define COMLINEARG_HPP
#include "dictionary.hpp"
#include <ostream>

namespace piyavkin
{
  void help(std::ostream& out);
  void check(std::ostream& out, const std::string& file);
}
#endif