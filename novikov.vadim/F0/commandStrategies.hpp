#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

#include "word.hpp"

namespace novikov
{
  struct KeyAndValueContain
  {
    static bool predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
    static std::istream& input(std::istream& in, Word::words_pair_t& rhs);
  };

  struct KeyContain
  {
    static bool predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
    static std::istream& input(std::istream& in, Word::words_pair_t& rhs);
  };

  struct ValueContain
  {
    static bool predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
    static std::istream& input(std::istream& in, Word::words_pair_t& rhs);
  };

  struct KeyAndValueEqual
  {
    static bool predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
    static std::istream& input(std::istream& in, Word::words_pair_t& rhs);
  };

  struct KeyEqual
  {
    static bool predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
    static std::istream& input(std::istream& in, Word::words_pair_t& rhs);
  };

  struct ValueEqual
  {
    static bool predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
    static std::istream& input(std::istream& in, Word::words_pair_t& rhs);
  };
}

#endif
