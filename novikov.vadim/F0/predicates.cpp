#include "predicates.hpp"

bool novikov::contains(const std::string& lhs, const std::string& rhs)
{
  return lhs.find(rhs) != std::string::npos;
}

bool novikov::containsKey(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return contains(lhs.first, rhs.first);
}

bool novikov::containsValue(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return contains(lhs.second, rhs.second);
}

bool novikov::containsKeyAndValue(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return containsKey(lhs, rhs) && containsValue(lhs, rhs);
}
