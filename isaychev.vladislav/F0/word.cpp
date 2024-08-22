#include "word.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>

bool is_letter(char c)
{
  return (c > '@' && c < '[') || (c > '`' && c < '{');
}

std::istream & isaychev::operator>>(std::istream & in, Word & w)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  std::string temp;
  in >> temp;
  if (std::ispunct(temp.back()))
  {
    temp.pop_back();
  }
  if (temp.find_first_of(')') != std::string::npos)
  {
    temp = temp.substr(0, temp.find_first_of(')'));
  }
  if (temp.find_last_of('(') != std::string::npos)
  {
    temp = temp.substr(temp.find_last_of('(') + 1);
  }
  if (std::none_of(temp.begin(), temp.end(), is_letter))
  {
    in.setstate(std::ios::failbit);
  }

  if (in)
  {
    w.content = std::move(temp);
  }

  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const Word & w)
{
  return out << w.content;
}

bool isaychev::operator<(const Word & lhs, const Word & rhs)
{
  return lhs.content < rhs.content;
}
