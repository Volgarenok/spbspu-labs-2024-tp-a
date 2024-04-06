#ifndef STRATEGIES_HPP
#define STRATEGIES_HPP

namespace ibragimov
{
  namespace formatters
  {
    struct CaseSensitive
    {
      static bool isSame(const char, const char);
    };
    struct CaseInsensitive
    {
      static bool isSame(const char, const char);
    };
  }
}

#endif
