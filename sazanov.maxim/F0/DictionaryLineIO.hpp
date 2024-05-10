#include "DictionaryLineIO.hpp"
#include <DelimiterI.hpp>

std::istream& sazanov::operator>>(std::istream& in, DictionaryLineI&& line)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> line.word >> StrictCaseDelimiterI{':'} >> line.frequency;
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, DictionaryLineIO&& line)
{
  out << line.word << " : " << line.frequency;
  return out;
}
