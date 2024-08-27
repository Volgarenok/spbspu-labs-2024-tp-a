#ifndef CLA_CMD_HPP
#define CLA_CMD_HPP

#include <iosfwd>
#include "freqList.hpp"

namespace isaychev
{
  void print_help(std::ostream & out);
  void load_saved(const std::string & file, std::map< std::string, FreqList > & col);
}

#endif
