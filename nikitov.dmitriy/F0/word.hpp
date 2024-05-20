#ifndef WORD_HPP
#define WORD_HPP

#include <string>

namespace nikitov
{
  namespace detail
  {
    struct Word
    {
      std::string translation_;
      std::string antonym_;

      Word(const std::string& translation, const std::string& antonym = "");
    };
  }
}
#endif