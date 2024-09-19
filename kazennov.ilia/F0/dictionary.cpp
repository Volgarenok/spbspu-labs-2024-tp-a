#include "dictionary.h"

std::istream& kazennov::operator>>(std::istream& in, WordForInput& word)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  WordForInput tmp;
  in >> tmp.word_;
  if (in)
  {
    word = tmp;
  }
  return in;
}

std::istream& kazennov::operator>>(std::istream& in, VectorOfDicts& word)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int n = 0;
  in >> n;
  if (n <= 0)
  {
    throw std::invalid_argument("INVALID ARGUMENT");
  }
  VectorOfDicts temp;
  using input_it_t = std::istream_iterator< WordForInput >;
  std::copy_n(input_it_t{ in }, n, std::back_inserter(temp.words_));
  if (in)
  {
    word = temp;
  }
  return in;
}

