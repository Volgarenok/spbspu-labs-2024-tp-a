#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

double vyzhanov::calculatePair(const Point& first, const Point& second)
{
  return first.x * second.y - second.x * first.y;
}
double vyzhanov::calculateArea(pnts begin, pnts end,
  pnts first, pnts second, double curr)
{
  if (second == end)
  {
    return 0.5 * std::fabs(curr + calculatePair(*first, *begin));
  }
  curr += calculatePair(*first, *second);
  return calculateArea(begin, end, ++first, ++second, curr);
}

double vyzhanov::getPolygonArea(const Polygon& polygon)
{
  return calculateArea(polygon.points.cbegin(), polygon.points.cend(),
    polygon.points.cbegin(), ++polygon.points.cbegin(), 0);
}

std::istream& vyzhanov::operator>>(std::istream& input, Polygon& polygon)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  size_t amount = 0;
  input >> amount;
  if (amount < 3)
  {
    input.setstate(std::ios::failbit);
  }
  std::vector< Point > tmp;
  std::copy_n( std::istream_iterator< Point >(input),
    amount, std::back_inserter(tmp));

  if (input && amount == tmp.size())
  {
    polygon.points = tmp;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::ostream& vyzhanov::operator<<(std::ostream& output, const Polygon& polygon)
{
  output << polygon.points.size() << " ";
  std::copy_n(polygon.points.cbegin(), polygon.points.size() - 1,
    std::ostream_iterator< Point >{ output, " " });
  output << polygon.points.back();
  return output;
}

bool vyzhanov::operator==(const Polygon& polygon1, const Polygon& polygon2)
{
  return polygon1.points == polygon2.points;
}
