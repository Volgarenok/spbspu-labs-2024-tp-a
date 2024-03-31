#include "inputFormatters.hpp"

#include "delimiters.hpp"
#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, DoubleLitI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    in >> std::noskipws;
    in >> dest.reference >> IgnoreCaseDelimiterI{"d"};
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
    in >> std::noskipws;
    in >> DelimiterI{"#c("} >> r >> std::ws >> i >> DelimiterI{")"};
    dest.reference.real(r);
    dest.reference.imag(i);
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    dest.reference.clear();
    char c = '\0';
    in >> std::noskipws;
    in >> DelimiterI{"\""};
    while ((in >> c) && (c != '"'))
    {
      if (c == '\\')
      {
        in >> c;
      }
      dest.reference.push_back(c);
    }
  }
  return in;
}
