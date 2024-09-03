#include "shapes.hpp"
#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <delimiters.hpp>

struct TriangleGeneration
{
  babinov::Triangle current;
  std::vector< babinov::Point > nextPoints;
  babinov::Triangle operator()();
};

babinov::Triangle TriangleGeneration::operator()()
{
  current.b = current.c;
  current.c = nextPoints.back();
  nextPoints.pop_back();
  return current;
}

double getArea(const babinov::Triangle& triangle)
{
  double a = babinov::Vector(triangle.a, triangle.b).getLength();
  double b = babinov::Vector(triangle.b, triangle.c).getLength();
  double c = babinov::Vector(triangle.a, triangle.c).getLength();
  double semiPer = (a + b + c) / 2;
  return std::sqrt(semiPer * (semiPer - a) * (semiPer - b) * (semiPer - c));
}

bool isPointFurther(const babinov::Point& basic, const babinov::Point& compared)
{
  return (compared.x > basic.x) && (compared.y > basic.y);
}

namespace babinov
{
  Vector::Vector(const Point& begin, const Point& end):
    coords(Point{end.x - begin.x, end.y - begin.y})
  {}

  double Vector::operator*(const Vector& other) const
  {
    return (coords.x * other.coords.x) + (coords.y * other.coords.y);
  }

  double Vector::getLength() const
  {
    return std::hypot(coords.x, coords.y);
  }

  double Vector::findCosBetween(const Vector& other) const
  {
    return (*this * other) / (getLength() * other.getLength());
  }

  bool setFailIfEndOfLine(std::istream& in)
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios::failbit);
    }
    return true;
  }

  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using del = CharDelimiterI;
    int x = 0;
    int y = 0;
    in >> del::insensitive('(') >> x >> del::insensitive(';') >> y >> del::insensitive(')');
    if (in)
    {
      point.x = x;
      point.y = y;
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    using input_it_t = std::istream_iterator< Point >;
    int nVertexes = 0;
    in >> nVertexes;
    if (nVertexes < 3)
    {
      polygon.points.clear();
      return in;
    }

    setFailIfEndOfLine(in);
    if (!in)
    {
      return in;
    }
    std::vector< Point > points;
    auto pred = std::bind(setFailIfEndOfLine, std::ref(in));
    std::copy_if(input_it_t(in), input_it_t(), std::back_inserter(points), pred);
    if (points.size() != (static_cast< size_t >(nVertexes)))
    {
      polygon.points.clear();
    }
    else
    {
      polygon.points = std::move(points);
      in.clear();
    }
    return in;
  }

  double getArea(const Polygon& polygon)
  {
    std::vector< Triangle > triangles(polygon.points.size() - 2);
    TriangleGeneration triangle{};
    triangle.current = Triangle{polygon.points[0], polygon.points[1], polygon.points[2]};
    triangle.nextPoints = std::vector< Point >(polygon.points.rbegin(), polygon.points.rend() - 3);
    triangles.push_back(triangle.current);
    std::generate_n(std::back_inserter(triangles), polygon.points.size() - 3, triangle);

    std::vector< double > areas(triangles.size());
    std::transform(triangles.cbegin(), triangles.cend(), std::back_inserter(areas), ::getArea);

    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  size_t getVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  bool isRectangle(const Polygon& polygon)
  {
    if (polygon.points.size() != 4)
    {
      return false;
    }
    Vector firstSide(polygon.points[0], polygon.points[1]);
    Vector secondSide(polygon.points[1], polygon.points[2]);
    Vector thirdSide(polygon.points[2], polygon.points[3]);
    Vector fourthSide(polygon.points[0], polygon.points[3]);
    bool isFirstRight = firstSide.findCosBetween(secondSide) == 0;
    bool isSecondRight = secondSide.findCosBetween(thirdSide) == 0;
    bool isThirdRight = thirdSide.findCosBetween(fourthSide) == 0;
    return isFirstRight && isSecondRight && isThirdRight;
  }

  bool isIntersect(const Polygon& first, const Polygon& second)
  {
    using namespace std::placeholders;
    auto fPts = std::minmax_element(first.points.cbegin(), first.points.cend(), isPointFurther);
    auto sPts = std::minmax_element(second.points.cbegin(), second.points.cend(), isPointFurther);
    bool isFirstIntersect = (!isPointFurther(*fPts.second, *sPts.first)) && (!isPointFurther(*sPts.second, *fPts.first));
    bool isSecondIntersect = (!isPointFurther(*sPts.second, *fPts.first)) && (!isPointFurther(*fPts.second, *sPts.first));
    return isFirstIntersect || isSecondIntersect;
  }
}
