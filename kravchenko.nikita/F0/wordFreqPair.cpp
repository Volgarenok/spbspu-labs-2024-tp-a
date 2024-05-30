#include "wordFreqPair.hpp"
#include <delimiterI.hpp>

std::istream& kravchenko::operator>>(std::istream& in, WordFreqPair& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  WordFreqPair temp;
  using cDel = DelimiterI< false >;
  if (in >> p.pairT.first >> cDel{ ':' } >> p.pairT.second)
  {
    p = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const WordFreqPair& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << p.pairT.first << " : " << p.pairT.second;
}
