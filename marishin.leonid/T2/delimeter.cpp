#include "delimeter.hpp"

std::istream& marishin::operator>>(std::istream& in, Delimeterchar&& exp)
{
  std::istream::sentry guard(in);
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& marishin::operator>>(std::istream& in, Delimeterstring&& exp)
{
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    if (std::isalpha(exp.expected[i]))
    {
      in >> Delimeterpair{ exp.expected[i++] };
    }
    else
    {
      in >> Delimeterchar{ exp.expected[i++] };
    }
  }
  return in;
}

std::istream& marishin::operator>>(std::istream& in, Delimeterpair&& exp)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = 0;
    in >> c;
    c = std::tolower(c);
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
