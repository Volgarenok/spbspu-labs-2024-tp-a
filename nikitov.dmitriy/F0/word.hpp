#ifndef WORD_HPP
#define WORD_HPP

#include <string>

namespace nikitov
{
  namespace detail
  {
    struct Word
    {
      std::pair< std::string, std::string > translations_;
      Word* antonym_;
    };
  }
}
#endif