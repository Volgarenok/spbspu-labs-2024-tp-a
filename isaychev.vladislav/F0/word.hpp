#ifndef WORD_HPP
#define WORD_HPP

#include <string>
#include <iosfwd>

namespace isaychev
{
  struct Word
  {
    std::string content;
  };

  std::istream & operator>>(std::istream & in, Word & w);
  std::ostream & operator<<(std::ostream & in, const Word & w);
  bool operator<(const Word & lhs, const Word & rhs);
}

#endif
