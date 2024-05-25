#include "word.hpp"
#include <stdexcept>
#include "delimiter.hpp"
#include "scope_guard.hpp"

#include <iostream>

nikitov::detail::Word::Word(const std::string& translation):
  primaryTranslation_(translation),
  secondaryTranslation_(),
  antonym_()
{}

std::string& nikitov::detail::Word::getPrimaryTranslation()
{
  return primaryTranslation_;
}

const std::string& nikitov::detail::Word::getPrimaryTranslation() const
{
  return primaryTranslation_;
}

std::string& nikitov::detail::Word::getSecondaryTranslation()
{
  return secondaryTranslation_;
}

const std::string& nikitov::detail::Word::getSecondaryTranslation() const
{
  return secondaryTranslation_;
}

std::string& nikitov::detail::Word::getAntonym()
{
  return antonym_;
}

const std::string& nikitov::detail::Word::getAntonym() const
{
  return antonym_;
}

std::istream& nikitov::detail::operator>>(std::istream& input, Word& word)
{
  ScopeGuard guard(input);

  std::string line;
  input >> line;
  if (line.back() == ';')
  {
    line.pop_back();
    word.getPrimaryTranslation() = line;
    return input;
  }
  else if (line.back() == ',')
  {
    line.pop_back();
    word.getPrimaryTranslation() = line;
    input >> line;
    if (line.back() == ';')
    {
      line.pop_back();
      word.getSecondaryTranslation() = line;
      return input;
    }
    else
    {
      word.getSecondaryTranslation() = line;
    }
  }
  else
  {
    word.getPrimaryTranslation() = line;
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
        word.getAntonym() = line;
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
  output << word.getPrimaryTranslation();
  if (!word.getSecondaryTranslation().empty())
  {
    output << ',' << ' ' << word.getSecondaryTranslation();
  }
  if (!word.getAntonym().empty())
  {
    output << ' ' << '(' << word.getAntonym() << ')';
  }
  return output;
}