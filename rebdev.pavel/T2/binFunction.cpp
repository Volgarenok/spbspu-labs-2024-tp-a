#include "binFunction.hpp"

#include <stack>

#include "streamGuard.hpp"

unsigned long long rebdev::inputBin(std::istream & in)
{
  StreamGuard guard(in);
  unsigned long long num = 0;

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
    num += (reverseStr.top() - '0') * pow;
    pow *= 2;
    reverseStr.pop();
  }

  return num;
}

void rebdev::outputBin(std::ostream & out, unsigned long long num)
{
  StreamGuard guard(out);

  std::stack< char > reverseBin;

  for (size_t i = 0; (num > 0); ++i)
  {
    reverseBin.push(('0' + (num % 2)));
    num /= 2;
  }

  size_t size = reverseBin.size();
  for (size_t i = 0; i < size; ++i)
  {
    out << reverseBin.top();
    reverseBin.pop();
  }

  if (size == 0) out << '0';
}
