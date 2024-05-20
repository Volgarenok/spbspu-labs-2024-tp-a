#include "word.hpp"

nikitov::detail::Word::Word(const std::string& translation, const std::string& antonym):
  translation_(translation),
  antonym_(antonym)
{}