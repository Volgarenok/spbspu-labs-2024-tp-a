#include "delimiter.hpp"
#include "inputFormatters.hpp"

std::istream& ibragimov::operator>>(std::istream& in, KeyIdI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    in >> StringDelimiterI{"key"};
    in >> std::noskipws;
    in >> dest.ref;
    in >> std::skipws;
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, DoubleLitI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    in >> std::noskipws;
    in >> dest.ref >> AnyCaseCharDelimiterI{'d'};
    in >> std::skipws;
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, ComplexLspI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    double r = 0.0;
    double i = 0.0;
    in >> StringDelimiterI{"#c"};
    in >> std::noskipws;
    in >> CharDelimiterI{'('} >> r >> std::ws >> i >> CharDelimiterI{')'};
    in >> std::skipws;
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
    dest.ref.clear();
    char c = ' ';
    in >> std::noskipws >> CharDelimiterI{'"'};
    while ((in >> c) && (c != '"'))
    {
      if (c == '\\')
      {
        in >> c;
      }
      dest.ref.push_back(c);
    }
    in >> std::skipws;
  }
  return in;
}
