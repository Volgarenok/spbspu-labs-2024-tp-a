#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <istream>

namespace novikov
{
  template < bool IgnoreCase >
  struct CharDelimiterI
  {
    char expected;
  };

  template < bool IgnoreCase >
  std::istream& operator>>(std::istream& in, const CharDelimiterI< IgnoreCase >& exp)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char ch{};
    in >> ch;
    const bool correct = (IgnoreCase && (std::tolower(ch) == std::tolower(exp.expected)))
                         || (!IgnoreCase && (ch == exp.expected));
    if (!correct)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  template < bool IgnoreCase >
  struct StringDelimiterI
  {
    const char* expected;
  };

  template< bool IgnoreCase >
  std::istream& operator>>(std::istream& in, const StringDelimiterI< IgnoreCase >& exp)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (const char* i = exp.expected; (*i != '\0') && in; ++i)
    {
      using chr_del = CharDelimiterI< IgnoreCase >;
      in >> chr_del{ *i };
    }
    return in;
  }
}

#endif
