#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include <string>
#include "word.hpp"

namespace novikov
{
  bool contains(const std::string& lhs, const std::string& rhs);
  bool containsKey(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
  bool containsValue(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
  bool containsKeyAndValue(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs);
}

#endif
