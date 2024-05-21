#include "word.hpp"

nikitov::detail::Word::Word(const std::string& translation):
  primaryTranslation_(translation),
  secondaryTranslation_(),
  antonym_()
{}