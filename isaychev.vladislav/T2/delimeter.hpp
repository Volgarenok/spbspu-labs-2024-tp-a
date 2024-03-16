#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <string>
#include <iosfwd>

namespace isaychev
{
  struct delim_ch_t
  {
    char expected;
  };
//  struct delim_ll_t
  struct delim_str_t
  {
    const char * exp;
  };

  std::istream & operator>>(std::istream & in, delim_ch_t && sym);
  std::istream & operator>>(std::istream & in, delim_str_t && key);
}

#endif
