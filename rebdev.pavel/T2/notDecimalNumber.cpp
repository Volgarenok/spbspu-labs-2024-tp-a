#include "notDecimalNumber.hpp"

#include <stack>
#include <cctype>

#include "streamGuard.hpp"

std::istream & rebdev::operator >> (std::istream & in, notDecimalNumber_t & num)
{
  std::istream::sentry sentryGuard(in);
  if (!sentryGuard) return in;

  if (num.basisOfNumSys_ < 2) return in;
  StreamGuard guard(in);

  num.data_ = 0;
  num.size_ = 0;

  in >> std::noskipws;

  char numNow = in.peek();
  std::stack< char > reverseStr;

  while (isCharInNumSys(numNow, num.basisOfNumSys_))
  {
    in >> numNow;
    reverseStr.push(numNow);
    ++num.size_;
    numNow = in.peek();
  }

  unsigned long long pow = 1;

  for (size_t i = 0; i < num.size_; ++i)
  {
    num.data_ += charToULL(reverseStr.top()) * pow;
    pow *= num.basisOfNumSys_;
    reverseStr.pop();
  }

  return in;
}


std::ostream & rebdev::operator << (std::ostream & out, const notDecimalNumber_t & num)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard) return out;

  if (num.basisOfNumSys_ < 2) return out;
  StreamGuard guard(out);

  unsigned long long dataCopy = num.data_;
  unsigned long long arr[num.size_] = {};

  for (size_t i = 0; i < num.size_; ++i)
  {
    arr[i] = (dataCopy % num.basisOfNumSys_);
    dataCopy /= num.basisOfNumSys_;
  }

  for (size_t i = num.size_; i > 0; --i)
  {
    out << ULLToChar(arr[i - 1]);
  }

  return out;
}

bool rebdev::isCharInNumSys(char c, char basisOfNumSys)
{
  bool low = 0, up = 0, dig = 0;

  if (basisOfNumSys <= 10)
  {
    dig = ((c >= '0') && (c <= ('0' + basisOfNumSys)));
  }
  else
  {
    dig = ((c >= '0') && (c <= '9'));
    low = ((c >= 'a') && (c <= ('a' + basisOfNumSys - 11)));
    up = ((c >= 'A') && (c <= ('A' + basisOfNumSys - 11)));
  }

  return (low || up || dig);
}
unsigned long long rebdev::charToULL(char c)
{
  if (std::isdigit(c))
  {
    return (c - '0');
  }
  else
  {
    c = std::tolower(c);
    return (c - 'a' + 10);
  }
}
char rebdev::ULLToChar(unsigned long long c)
{
  if (c < 10)
  {
    return ('0' + c);
  }
  else
  {
    return ('A' + c - 10);
  }
}
