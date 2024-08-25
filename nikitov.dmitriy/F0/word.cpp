#include "word.hpp"
#include <iostream>
#include <stdexcept>
#include "delimiter.hpp"

nikitov::detail::Word::Word(const std::string& primary, const std::string& secondary, const std::string& antonym) :
  primaryTranslation(primary),
  secondaryTranslation(secondary),
  antonym(antonym)
{}

std::istream& nikitov::detail::operator>>(std::istream& input, Word& word)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

  char lastSymb = ' ';
  std::string translation;
  input >> translation;

  lastSymb = translation.back();
  translation.pop_back();
  word.primaryTranslation = translation;
  if (lastSymb == ',')
  {
    input >> translation;
    lastSymb = translation.back();
    translation.pop_back();
    word.secondaryTranslation = translation;
  }
  if (lastSymb == ';')
  {
    return input;
  }
  input >> DelimiterChar({ '(' });
  if (input)
  {
    input >> translation;
    lastSymb = translation.back();
    translation.pop_back();
    if (lastSymb == ';' && translation.back() == ')')
    {
      translation.pop_back();
      word.antonym = translation;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
  }
  return input;
}

std::ostream& nikitov::detail::operator<<(std::ostream& output, const Word& word)
{
  output << word.primaryTranslation;
  if (!word.secondaryTranslation.empty())
  {
    output << ", " << word.secondaryTranslation;
  }
  if (!word.antonym.empty())
  {
    output << " (" << word.antonym << ')';
  }
  output << ';';
  return output;
}
