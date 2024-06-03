#include "predicates.hpp"
#include <algorithm>

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

bool novikov::equalsKey(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return lhs.first == rhs.first;
}

bool novikov::equalsValue(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return lhs.second == rhs.second;
}

bool novikov::equalsKeyAndValue(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return equalsKey(lhs, rhs) && equalsValue(lhs, rhs);
}

bool novikov::found(const Dictionary& lhs, const Dictionary::value_type& rhs)
{
  return std::find(lhs.cbegin(), lhs.cend(), rhs) != lhs.cend();
}

bool novikov::notFound(const Dictionary& lhs, const Dictionary::value_type& rhs)
{
  return !found(lhs, rhs);
}

bool novikov::foundInBoth(const Dictionary& lhs, const Dictionary& rhs, const Dictionary::value_type& value)
{
  return found(lhs, value) && found(rhs, value);
}

bool novikov::notFoundInBoth(const Dictionary& lhs, const Dictionary& rhs, const Dictionary::value_type& value)
{
  return !foundInBoth(lhs, rhs, value);
}
