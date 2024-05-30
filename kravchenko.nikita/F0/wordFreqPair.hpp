#ifndef WORD_FREQ_PAIR_HPP
#define WORD_FREQ_PAIR_HPP

#include <string>
#include <utility>
#include <istream>
#include <ostream>

namespace kravchenko
{
  struct WordFreqPair
  {
    std::pair< std::string, size_t > pairT;
  };
  std::istream& operator>>(std::istream& in, WordFreqPair& p);
  std::ostream& operator<<(std::ostream& out, const WordFreqPair& p);
}

#endif
