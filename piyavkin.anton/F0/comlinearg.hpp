#ifndef COMLINEARG_HPP
#define COMLINEARG_HPP
#include <ostream>

namespace piyavkin
{
  void help(std::ostream& out);
  void check(std::istream& in, std::ostream& out);
}
#endif