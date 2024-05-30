#include "number_format.hpp"
#include <iostream>
#include <iomanip>
#include "scope_guard.hpp"

std::ostream & erohin::operator<<(std::ostream & output, NumberFormat && numformat)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  ScopeGuard sg(output);
  switch (numformat.format)
  {
  case NUMBER:
    output << numformat.number;
    break;
  case PROPORTION:
    output << numformat.number << " / " << numformat.size;
    break;
  case FRACTIONAL:
    output << std::setprecision(6) << std::fixed << static_cast< double >(numformat.number) / numformat.size;
    break;
  case PERCENTAGE:
    output << std::setprecision(4) << std::fixed << static_cast< double >(numformat.number) / numformat.size * 100 << " %";
    break;
  }
  return output;
}
