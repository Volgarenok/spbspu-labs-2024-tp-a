#include "word.hpp"
#include <stdexcept>

nikitov::detail::Word::Word(const std::string& translation):
  primaryTranslation_(translation),
  secondaryTranslation_(),
  antonym_()
{}

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