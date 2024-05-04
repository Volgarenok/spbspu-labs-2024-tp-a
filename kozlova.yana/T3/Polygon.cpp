#include "Polygon.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include "Delimiter.h"

std::istream& kozlova::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
      return in;
  }

  in >> DelimiterCharIO{ '(' } >> point.x >> DelimiterCharIO{ ';' } >> point.y >> DelimiterCharIO{ ')' };
  return in;
}
