#ifndef WORD_FREQ_PAIR_HPP
#define WORD_FREQ_PAIR_HPP

#include <istream>
#include <ostream>
#include <string>
#include <utility>

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
