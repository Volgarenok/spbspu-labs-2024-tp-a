#include "RealisationKeys.h"
#include <iomanip>
#include "DataStruct.h"
#include "Delimiter.h"

std::istream& kartamyshev::operator>>(std::istream& in, DoubleKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> key.num;
  return in;
}

std::ostream& kartamyshev::print(std::ostream& out, double num)
{
  int expon = 0;
  char sym = ' ';
  double current = num ;
  if (current != 0)
  {
    if (current >= 1.0)
    {
      while (current > 1.0)
      {
        current = current / 10;
        expon++;
      }
      sym = '+';
    }
    else
    {
      while (current < 1.0)
      {
        current = current * 10;
        expon++;
      }
      sym = '-';
    }
    out << std::fixed << current << 'e' << sym << expon;
  }
  else
  {
    out << std::fixed << current;
  }
  return out;
}

std::istream& kartamyshev::operator>>(std::istream& in, LLKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using delS = DelimiterStr;
  in >> key.num >> delS{ "ll" };
  return in;
}

std::istream& kartamyshev::operator>>(std::istream& in, StrKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = DelimiterSym;
  in >> del{ '"' };
  std::getline(in, key.string, '"');
  return in;
}

