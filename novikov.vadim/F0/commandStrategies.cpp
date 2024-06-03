#include "commandStrategies.hpp"
#include <string>
#include "predicates.hpp"
#include "customAlgorithms.hpp"

bool novikov::KeyAndValueContain::predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return containsKeyAndValue(lhs, rhs);
}

std::istream& novikov::KeyAndValueContain::input(std::istream& in, Word::words_pair_t& rhs)
{
  return readKeyAndValue< std::string, std::string >(in, rhs);
}

bool novikov::KeyContain::predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return containsKey(lhs, rhs);
}

std::istream& novikov::KeyContain::input(std::istream& in, Word::words_pair_t& rhs)
{
  return readKey< std::string, std::string >(in, rhs);
}

bool novikov::ValueContain::predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return containsValue(lhs, rhs);
}

std::istream& novikov::ValueContain::input(std::istream& in, Word::words_pair_t& rhs)
{
  return readValue< std::string, std::string >(in, rhs);
}

bool novikov::KeyAndValueEqual::predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return std::equal_to< std::pair< std::string, std::string > >()(lhs, rhs);
}

std::istream& novikov::KeyAndValueEqual::input(std::istream& in, Word::words_pair_t& rhs)
{
  return readKeyAndValue< std::string, std::string >(in, rhs);
}

bool novikov::KeyEqual::predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return equalsKey(lhs, rhs);
}

std::istream& novikov::KeyEqual::input(std::istream& in, Word::words_pair_t& rhs)
{
  return readKey< std::string, std::string >(in, rhs);
}

bool novikov::ValueEqual::predicate(const Word::const_words_pair_t& lhs, const Word::const_words_pair_t& rhs)
{
  return equalsValue(lhs, rhs);
}

std::istream& novikov::ValueEqual::input(std::istream& in, Word::words_pair_t& rhs)
{
  return readValue< std::string, std::string >(in, rhs);
}
