#include "polygon.hpp"

#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iostream>

//#include <delimiter.hpp>

std::istream& gladyshev::operator>>(std::istream& in, Point& pnt)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimiter{"("} >> pnt.x >> Delimiter{";"} >> pnt.y >> Delimiter{")"};
  return in;
}
bool gladyshev::operator==(const Point& left, const Point& right)
{
  return (left.x == right.x) && (left.y == right.y);
}
bool gladyshev::operator==(const Polygon& left, const Polygon& right)
{
  if (left.points.size() != right.points.size())
  {
    return false;
  }
  return std::equal(left.points.cbegin(), left.points.cend(), right.points.cbegin());
}
std::istream& gladyshev::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t num = 0;
  in >> num;
  if (num < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  poly.points.clear();
  std::copy_n(
    std::istream_iterator< Point >(in),
    num,
    std::back_inserter(poly.points)
  );
  return in;
}

namespace gladyshev
{
  struct TriangleArea
  {
    double operator()(const Point& a, const Point& b, const Point& c) const
    {
      return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
    }
  };
}

double gladyshev::findArea(const Polygon& poly)
{
  using namespace std::placeholders;
  Point center{0, 0};
  auto cmpX = [](const Point& a, const Point& b)
    {
      return a.x < b.x;
    };
  auto cmpY = [](const Point& a, const Point& b)
    {
      return a.y < b.y;
    };
  auto cenX = std::minmax_element(poly.points.begin(), poly.points.end(), cmpX);
  auto cenY = std::minmax_element(poly.points.begin(), poly.points.end(), cmpY);
  center.x = (cenX.first->x + cenX.second->x) / 2.0;
  center.y = (cenY.first->y + cenY.second->y) / 2.0;
  std::vector< double > areas(poly.points.size());
  TriangleArea triangleArea;
  std::transform(poly.points.begin(), poly.points.end() - 1, poly.points.begin() + 1, areas.begin(),
    std::bind(triangleArea, _1, _2, center));
  areas.back() = triangleArea(*(poly.points.end() - 1), poly.points.front(), center);
  return std::accumulate(areas.begin(), areas.end(), 0.0);
}
