#include "word.hpp"
#include <stdexcept>

nikitov::detail::Word::Word(const std::string& translation):
  primaryTranslation_(translation),
  secondaryTranslation_(),
  antonym_()
{}

std::ostream& nikitov::detail::Word::operator<<(std::ostream& output)
{
  output << primaryTranslation_;
  if (!secondaryTranslation_.empty())
  {
    output << ' ' << secondaryTranslation_;
  }
  if (!antonym_.empty())
  {
    output << ' ' << '(' << antonym_ << ')';
  }
}

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