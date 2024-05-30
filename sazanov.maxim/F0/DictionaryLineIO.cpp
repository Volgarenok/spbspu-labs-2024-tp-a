#include "DictionaryLineIO.hpp"
#include <DelimiterI.hpp>

std::istream& sazanov::operator>>(std::istream& in, DictionaryLineI& line)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  std::pair< std::string , size_t > temp;
  in >> temp.first >> StrictCaseDelimiterI{':'} >> temp.second;
  if (in)
  {
    line.pair = temp;
  }
  if (in.get() != '\n')
  {
    in.setstate(std::ios::failbit);
  }
  if (in.peek() == EOF)
  {
    in.setstate(std::ios::eofbit);
  }
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const DictionaryLineO& line)
{
  out << line.pair.first << " : " << line.pair.second;
  return out;
}
