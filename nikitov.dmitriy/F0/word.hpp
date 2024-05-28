#ifndef WORD_HPP
#define WORD_HPP

#include <ostream>
#include <utility>
#include <string>

namespace nikitov
{
  namespace detail
  {
    struct Word
    {
      Word() = default;
      Word(const std::string& translation);
      ~Word() = default;

      std::string primaryTranslation;
      std::string secondaryTranslation;
      std::string antonym;
    };

    std::istream& operator>>(std::istream& input, Word& word);
    std::ostream& operator<<(std::ostream& output, const Word& word);
  }
}
#endif