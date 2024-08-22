#ifndef FREQLISTVALUE_HPP
#define FREQLISTVALUE_HPP

#include <map>
#include "word.hpp"

namespace isaychev
{
  struct FreqList
  {
    void insert(const Word & rhs);

    std::map< Word, size_t > list;
  };
}

#endif
