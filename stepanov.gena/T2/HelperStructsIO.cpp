#include "HelperStructsIO.h"

stepanov::DelimeterIO::DelimeterIO(char exp):
  exp_(exp)
{}

stepanov::LabelIO::LabelIO(std::string exp):
  exp_(exp)
{}

std::istream& stepanov::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && c != dest.exp_ && (c != std::toupper(dest.exp_)))
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
  if (in && (data != dest.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
