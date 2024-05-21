#include "word.hpp"
#include <stdexcept>
#include "delimiter.hpp"
#include "scope_guard.hpp"

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
  input >> std::noskipws;

  std::string line = {};
  char symb = {};
  while (input >> symb && (symb != '\n' && symb != ' ' && symb != ','))
  {
    line += symb;
  }
  word.getPrimaryTranslation() = line;
  line = {};

  if (symb == ',')
  {
    input >> std::skipws;
    input >> word.getSecondaryTranslation();
    input >> std::noskipws;
  }

  input >> symb;
  if (symb != '\n')
  {
    while (input >> symb && symb != ')')
    {
      line += symb;
    }
    word.getAntonym() = line;
  }
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
}