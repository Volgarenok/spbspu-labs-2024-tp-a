#include "DictionaryLineIO.hpp"
#include <DelimiterI.hpp>

std::istream& sazanov::operator>>(std::istream& in, DictionaryLineI& line)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> line.pair.first >> StrictCaseDelimiterI{':'} >> line.pair.second;
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const DictionaryLineO& line)
{
  out << line.pair.first << " : " << line.pair.second;
  return out;
}

sazanov::DictionaryLineO sazanov::getDictionaryLineO(const std::pair< std::string, size_t >& pair)
{
  return DictionaryLineO{pair};
}
