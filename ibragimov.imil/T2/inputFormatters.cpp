#include "inputFormatters.hpp"

#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, KeyIdI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    in >> std::noskipws
       >> StringDelimiterI{"key"} >> dest.ref;
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, DoubleLitI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    in >> std::noskipws
       >> dest.ref >> AnyCaseCharDelimiterI{'d'};
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, ComplexLspI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    double r = 0.0;
    double i = 0.0;
    in >> std::noskipws
       >> StringDelimiterI{"#c"} >> CharDelimiterI{'('} >> r >> std::ws >> i >> CharDelimiterI{')'};
    dest.ref.real(r);
    dest.ref.imag(i);
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    dest.ref.clear();
    char c = ' ';
    in >> std::noskipws
       >> CharDelimiterI{'"'};
    while ((in >> c) && (c != '"'))
    {
      if (c == '\\')
      {
        in >> c;
      }
      dest.ref.push_back(c);
    }
  }
  return in;
}
