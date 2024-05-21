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

const std::string& nikitov::detail::Word::getAntonym() const
{
  return antonym_;
}

void nikitov::detail::Word::addTranslation(const std::string& translation)
{
  if (secondaryTranslation_.empty())
  {
    secondaryTranslation_ = translation;
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::detail::Word::addAntonym(const std::string& antonym)
{
  antonym_ = antonym;
}