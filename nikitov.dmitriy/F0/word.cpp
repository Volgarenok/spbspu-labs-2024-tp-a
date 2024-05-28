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
  std::string line;
  input >> line;
  if (line.back() == ';')
  {
    line.pop_back();
    word.primaryTranslation = line;
    return input;
  }
  else if (line.back() == ',')
  {
    line.pop_back();
    word.primaryTranslation = line;
    input >> line;
    if (line.back() == ';')
    {
      line.pop_back();
      word.secondaryTranslation = line;
      return input;
    }
    else
    {
      word.secondaryTranslation = line;
    }
  }
  else
  {
    word.primaryTranslation = line;
  }

  input >> DelimiterChar({'('});
  if (input)
  {
    input >> line;
    if (line.back() == ';')
    {
      line.pop_back();
      if (line.back() == ')')
      {
        line.pop_back();
        word.antonym = line;
      }
      else
      {
        input.setstate(std::ios::failbit);
      }
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