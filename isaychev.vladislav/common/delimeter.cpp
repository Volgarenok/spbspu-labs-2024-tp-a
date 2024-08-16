#include "delimeter.hpp"
#include <iostream>

std::istream & isaychev::operator>>(std::istream & in, DelimChI && sym)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (in && std::tolower(c) != sym.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, DelimStrI && seq)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  bool isCorrectStr = true;
  for (int i = 0; seq.exp[i] != '\0'; ++i)
  {
    in >> c;
    if (in && seq.exp[i] != c)
    {
      isCorrectStr = false;
    }
  }
  if (!isCorrectStr)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, LongLongI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string data = "";
  char c = 0;
  in >> c;
  while (!std::isalpha(c))
  {
    data.push_back(c);
    in >> c;
  }
  data.push_back(c);
  in >> c;
  data.push_back(c);
  try
  {
    dest.ref = std::stoll(data);
  }
  catch (const std::invalid_argument &)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, ComplexI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  double real = 0, imag = 0;
  in >> DelimStrI{"#c("} >> real >> DelimChI{' '} >> imag >> DelimChI{')'};

  if (!in)
  {
    in.setstate(std::ios::failbit);
  }

  dest.ref = {real, imag};
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, StringI && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> DelimChI{'"'};
  std::getline(in, dest.ref, '"');
  return in;
}
