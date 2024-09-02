#ifndef WORD_HPP
#define WORD_HPP

#include <istream>
#include <ostream>
#include <string>

namespace novikov
{
  struct Word
  {
    using words_pair_t = std::pair< std::string, std::string >;
    using const_words_pair_t = std::pair< const std::string, std::string >;
    words_pair_t value;
  };

  std::istream& operator>>(std::istream& in, Word& rhs);
  std::ostream& operator<<(std::ostream& out, const Word& rhs);

  Word toWord(const Word::words_pair_t& rhs);
  const Word::words_pair_t& toPair(const Word& rhs);
}

#endif
