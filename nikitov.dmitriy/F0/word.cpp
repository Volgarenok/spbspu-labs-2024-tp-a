#include "word.hpp"
#include <stdexcept>
#include "delimiter.hpp"

#include <iostream>

nikitov::detail::Word::Word(const std::string& translation):
  primaryTranslation(translation),
  secondaryTranslation(),
  antonym()
{}

std::istream& nikitov::detail::operator>>(std::istream& input, Word& word)
{
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
  input >> DelimiterChar({'('});
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
}

std::ostream& nikitov::detail::operator<<(std::ostream& output, const Word& word)
{
  output << word.primaryTranslation;
  if (!word.primaryTranslation.empty())
  {
    output << ',' << ' ' << word.secondaryTranslation;
  }
  if (!word.antonym.empty())
  {
    output << ' ' << '(' << word.antonym << ')';
  }
  output << ';';
  return output;
}