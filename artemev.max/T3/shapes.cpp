#include "shapes.hpp"
#include <istream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <Delimiter.hpp>

struct AccumulateArea
{
  artemev::Point first;
  double operator()(double area, const artemev::Point& second, const artemev::Point& third);
};

struct AccumulateAngle
{
  artemev::Point first, second;
  bool operator()(const artemev::Point& third);
};

std::istream& artemev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using delChar = artemev::DelimiterCharI;
  int x, y;
  in >> delChar({'('}) >> x >> delChar({';'}) >> y >> delChar({')'});
  if (in)
  {
    point.x = x;
    point.y = y;
  }
  return in;
}

bool artemev::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

std::istream& artemev::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int countTop;
  in >> countTop;
  if (countTop < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >{ in }, countTop, std::back_inserter(points));

  if (in)
  {
    polygon.points = std::move(points);
  }

  return in;
}

double artemev::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AccumulateArea{ polygon.points.at(1) }, _1, _2, polygon.points.at(0));
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}

double countArea(const artemev::Point& first, const artemev::Point& second, const artemev::Point& third)
{
  return std::abs((second.x - first.x) * (third.y - first.y) - (third.x - first.x) * (second.y - first.y)) / 2;
}

double AccumulateArea::operator()(double area, const artemev::Point& second, const artemev::Point& third)
{
  area += countArea(first, second, third);
  first = second;
  return area;
}

size_t artemev::countRightAngle(const Polygon& polygon)
{
  auto countAngle = AccumulateAngle{ polygon.points[polygon.points.size() - 1], polygon.points[polygon.points.size() - 2] };
  return std::count_if(polygon.points.cbegin(), polygon.points.cend(), countAngle);
}

artemev::Point calculateSide(const artemev::Point& first, const artemev::Point& second)
{
  return {second.x - first.x, second.y - first.y};
}

bool AccumulateAngle::operator()(const artemev::Point& third)
{
  artemev::Point side1 = calculateSide(first, second);
  artemev::Point side2 = calculateSide(first, third);

  first = second;
  second = third;

  return side1.x * side2.x + side1.y * side2.y == 0;
}
