#include "HelperStructsIO.h"

stepanov::DelimeterIO::DelimeterIO(char exp):
  exp_(exp)
{}

char stepanov::DelimeterIO::getExp() const
{
  return exp_;
}

stepanov::LabelIO::LabelIO(std::string exp):
  exp_(exp)
{}

std::string stepanov::LabelIO::getExp() const
{
  return exp_;
}

std::istream& stepanov::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && c != dest.getExp() && (c != std::toupper(dest.getExp())))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& stepanov::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  in >> data;
  if (in && (data != dest.getExp()))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
