#include "polygon.hpp"
#include <iterator>
#include <algorithm>

double vyzhanov::calculatePair(const Point& first, const Point& second)
{
  return first.x * second.y - first.y * second.x;
}

double vyzhanov::calculateArea(points begin, points end,
  points first, points second, double curr)
{
  if (second == end)
  {
    return 0.5 * std::abs(curr + calculatePair(*first, *begin));
  }
  curr += calculatePair(*first, *second);
  return calculateArea(begin, end, ++first, ++second, curr);

}

double vyzhanov::getArea(const Polygon& poly)
{
  return calculateArea(poly.polygon.cbegin(), poly.polygon.cend(),
           poly.polygon.cbegin(), ++poly.polygon.cbegin(), 0);
}

std::istream& vyzhanov::operator>>(std::istream& input, Polygon& poly)
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
  std::vector< Point > points;
  std::copy_n( std::istream_iterator< Point >(input),
    amount, std::back_inserter(points));

  if (input && amount == points.size())
  {
    poly.polygon = points;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::ostream& vyzhanov::operator<<(std::ostream& output, const Polygon& poly)
{
  output << poly.polygon.size() << " ";
  std::copy_n(poly.polygon.cbegin(), poly.polygon.size() - 1,
    std::ostream_iterator< Point >{ output, " " });
  output << poly.polygon.back();
  return output;
}

bool vyzhanov::operator==(const Polygon& poly1, const Polygon& poly2)
{
  return poly1.polygon == poly2.polygon;
}
