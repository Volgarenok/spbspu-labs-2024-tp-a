#ifndef FREQLISTVALUE_HPP
#define FREQLISTVALUE_HPP

#include <map>
#include <iosfwd>
#include "word.hpp"

namespace isaychev
{
  struct FreqList
  {
    void insert(const Word & rhs);
    void add_element(const std::pair< Word, size_t > & rhs);

    std::map< Word, size_t > list;
  };

  std::ostream & operator<<(std::ostream & out, const FreqList & rhs);
  std::string convert_to_str(const std::pair< Word, size_t > & rhs);
}

#endif
