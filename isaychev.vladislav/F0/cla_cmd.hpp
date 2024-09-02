#ifndef NON_INTERACTIVE_CMD_HPP
#define NON_INTERACTIVE_CMD_HPP

#include <iosfwd>
#include "freqList.hpp"

namespace isaychev
{
  using collection_t = std::map< std::string, FreqList >;

  void print_help(std::ostream & out);
  void load_saved(collection_t & col);
  void save(const collection_t & col);
}

#endif
