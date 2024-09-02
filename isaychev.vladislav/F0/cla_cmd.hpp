#ifndef CLA_CMD_HPP
#define CLA_CMD_HPP

#include <iosfwd>
#include "freqList.hpp"

namespace isaychev
{
  using collection_t = std::map< std::string, FreqList >;

  void print_help(std::ostream & out);
  void load_saved(const std::string & file, collection_t & col);
}

#endif
