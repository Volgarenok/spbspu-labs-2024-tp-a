#ifndef WORD_HPP
#define WORD_HPP

#include <iostream>
#include <string>

namespace nikitov
{
  namespace detail
  {
    struct Word
    {
      Word(const std::string& primary = "", const std::string& secondary = "", const std::string& antonym = "");
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
