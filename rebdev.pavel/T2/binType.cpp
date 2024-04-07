#include "binType.hpp"

#include <stack>

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool rebdev::binType::operator==(const binType & bin) const noexcept
{
  return data_ == bin.data_;
}

bool rebdev::binType::operator<(const binType & bin) const noexcept
{
  return data_ < bin.data_;
}

std::istream & rebdev::operator>>(std::istream & in, binType & bin)
{
  bin.data_ = 0;
  std::istream::sentry sentryGuard(in);
  if(!sentryGuard)  return in;
  StreamGuard guard(in);

  in >> delimeter_t{'0'} >> delimeter_t{'b'};

  in >> std::noskipws;

  char numNow = in.peek();
  std::stack< char > reverseStr;

  while ((numNow == '0') || (numNow == '1'))
  {
    in >> numNow;
    reverseStr.push(numNow);
    numNow = in.peek();
  }

  unsigned long long pow = 1;
  size_t size = reverseStr.size();

  for (size_t i = 0; i < size; ++i)
  {
    bin.data_ += (reverseStr.top() - '0') * pow;
    pow *= 2;
    reverseStr.pop();
  }

  return in;
}

std::ostream & rebdev::operator<<(std::ostream & out, const binType & bin)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard) return out;
  StreamGuard guard(out);

  out << "0b";

  std::stack< char > reverseBin;

  unsigned long long num = bin.data_;

  for (size_t i = 0; (num > 0); ++i)
  {
    reverseBin.push(('0' + (num % 2)));
    num /= 2;
  }

  out << '0';

  size_t size = reverseBin.size();
  for (size_t i = 0; i < size; ++i)
  {
    out << reverseBin.top();
    reverseBin.pop();
  }

  return out;
}

