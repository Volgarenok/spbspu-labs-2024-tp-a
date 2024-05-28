#include "word.hpp"
#include <utility>
#include <delimiterI.hpp>

std::istream& novikov::operator>>(std::istream& in, Word& rhs)
{
  std::istream::sentry sentry(in);

  if (!sentry)
  {
    return in;
  }

  std::string original;
  std::string translation;

  in >> original >> StrictCaseStringDelimiterI{ "-" } >> translation;

  if (in)
  {
    rhs.value.first = original;
    rhs.value.second = std::move(translation);
  }

  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Word& rhs)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  out << rhs.value.first << " - " << rhs.value.second;
  return out;
}

novikov::Word novikov::toWord(const Word::words_pair_t& rhs)
{
  return Word{ std::move(rhs) };
}

const novikov::Word::words_pair_t& novikov::toPair(const Word& rhs)
{
  return rhs.value;
}
