#include "KeyType.h"
#include <iomanip>
#include "DataStruct.h"
#include <Delimiter.h>

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

std::ostream& kartamyshev::operator<<(std::ostream& out, const DoubleKeyOut&& key)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  int expon = 0;
  char sym = ' ';
  double current = key.num;

  if (current != 0)
  {
    while (current >= 10.0 || current < 1.0)
    {
      if (current >= 10.0)
      {
        current /= 10;
        expon++;
      }
      else
      {
        current *= 10;
        expon--;
      }
    }
    sym = (expon >= 0) ? '+' : '-';
  }
  else
  {
    out << std::fixed << current;
  }
  out << std::fixed << current << 'e' << sym << std::abs(expon);
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

