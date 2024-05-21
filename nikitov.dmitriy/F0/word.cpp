#include "word.hpp"
#include <stdexcept>

nikitov::detail::Word::Word(const std::string& translation):
  primaryTranslation_(translation),
  secondaryTranslation_(),
  antonym_()
{}

std::string& nikitov::detail::Word::getPrimaryTranslation()
{
  return primaryTranslation_;
}

std::string& nikitov::detail::Word::getSecondaryTranslation()
{
  return secondaryTranslation_;
}

std::string& nikitov::detail::Word::getAntonym()
{
  return antonym_;
}