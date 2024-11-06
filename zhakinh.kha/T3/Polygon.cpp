#include "Polygon.hpp"
#include <cmath>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>

std::istream& zhakha::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  Point temp{0,0};
  char ch;
  in >> ch >> temp.x >> ch >> temp.y >> ch;
  if (in)
  {
    point = temp;
  }

  return in;
}

std::ostream& zhakha::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool zhakha::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& zhakha::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  size_t n{};
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector<Point> points(n);
  using input_it_t = std::istream_iterator<Point>;
  std::copy_n(input_it_t{ in }, n, points.begin());
  if (in && points.size() == n)
  {
    polygon.points = std::move(points);
  }

  return in;
}

bool zhakha::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}

int zhakha::getDeterminantByPoint(const Polygon& polygon, const Point& point)
{
  size_t index = std::distance(polygon.points.cbegin(), std::find(polygon.points.cbegin(), polygon.points.cend(), point));
  size_t size = polygon.points.size();

  int x1 = polygon.points.at(index % size).x;
  int y1 = polygon.points.at(index % size).y;
  int x2 = polygon.points.at((index + 1) % size).x;
  int y2 = polygon.points.at((index + 1) % size).y;

  return x1 * y2 - y1 * x2;
}

double zhakha::getArea(const Polygon& polygon)
{
  std::vector<int> dets(polygon.points.size());
  auto oper = std::bind(getDeterminantByPoint, std::cref(polygon), std::placeholders::_1);
  std::transform(polygon.points.cbegin(), polygon.points.cend(), dets.begin(), oper);
  return 0.5 * std::abs(std::accumulate(dets.cbegin(), dets.cend(), 0));
}
