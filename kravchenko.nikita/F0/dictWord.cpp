#include "dictWord.hpp"
#include <regex>

std::istream& kravchenko::operator>>(std::istream& in, DictWord&& dWord)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string temp;
  in >> temp;

  static const std::regex wordRegex(R"([A-Za-z](([A-Za-z\-']*[A-Za-z])|([A-Za-z]*)))");
  std::smatch wordMatch;
  if (std::regex_search(temp, wordMatch, wordRegex))
  {
    dWord.word = wordMatch.str();
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}