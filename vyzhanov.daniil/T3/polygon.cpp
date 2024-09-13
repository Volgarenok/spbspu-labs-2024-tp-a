#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

double vyzhanov::getTriangleArea(const Point& p1, const Point& p2, const Point& p3)
{
  size_t radical = (p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y);
  return 0.5 * std::fabs(radical);
}

double vyzhanov::getPolygonArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }
  std::vector< double > triangleAreas(polygon.points.size() - 2);
  using namespace std::placeholders;
  std::transform(polygon.points.begin() + 2, polygon.points.end(), std::next(polygon.points.begin(), 1),
    triangleAreas.begin(), std::bind(getTriangleArea, polygon.points[0], _1, _2));
  return std::accumulate(triangleAreas.begin(), triangleAreas.end(), 0.0);
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
