#include "shapes.hpp"
#include <algorithm>
#include <cmath>
#include <delimiters.hpp>
#include <ios>
#include <iostream>
#include <iterator>
#include <numeric>

namespace babinov
{
  bool Point::operator<(const Point& other) const
  {
    return (x < other.x) && (y < other.y);
  }

  bool Point::operator>=(const Point& other) const
  {
    return !(*this < other);
  }

  bool Point::operator<=(const Point& other) const
  {
    return !(other < *this);
  }

  Vector::Vector(const Point& begin, const Point& end):
    coords(Point{end.x - begin.x, end.y - begin.y})
  {}

  double Vector::operator*(const Vector& other) const
  {
    return (coords.x * other.coords.x) + (coords.y * other.coords.y);
  }

  double Vector::getLength() const
  {
    return std::sqrt(std::pow(coords.x, 2) + std::pow(coords.y, 2));
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
    if (points.size() != (static_cast<size_t>(nVertexes)))
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

  double getArea(const Triangle& triangle)
  {
    double a = Vector(triangle.a, triangle.b).getLength();
    double b = Vector(triangle.b, triangle.c).getLength();
    double c = Vector(triangle.a, triangle.c).getLength();
    double semiPer = (a + b + c) / 2;
    return std::sqrt(semiPer * (semiPer - a) * (semiPer - b) * (semiPer - c));
  }

  double addPolygonPartArea(double currentArea, Triangle& prevPart, const Point& newPt)
  {
    prevPart.b = prevPart.c;
    prevPart.c = newPt;
    return currentArea += getArea(prevPart);
  }

  double getArea(const Polygon& polygon)
  {
    using namespace std::placeholders;
    Triangle areaPart{polygon.points[0], polygon.points[1], polygon.points[2]};
    double area = getArea(areaPart);
    if (polygon.points.size() > 3)
    {
      auto operation = std::bind(addPolygonPartArea, _1, std::ref(areaPart), _2);
      area += std::accumulate(polygon.points.cbegin() + 3, polygon.points.cend(), 0.0, operation);
    }
    return area;
  }

  int getVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  bool isRectangle(const Polygon& polygon)
  {
    if (polygon.points.size() == 4)
    {
      Vector firstSide(polygon.points[0], polygon.points[1]);
      Vector secondSide(polygon.points[1], polygon.points[2]);
      Vector thirdSide(polygon.points[2], polygon.points[3]);
      Vector fourthSide(polygon.points[0], polygon.points[3]);
      return (firstSide.findCosBetween(secondSide) == 0)
          && (secondSide.findCosBetween(thirdSide) == 0)
          && (thirdSide.findCosBetween(fourthSide) == 0);
    }
    return false;
  }

  bool isIntersect(const Polygon& first, const Polygon& second)
  {
    using namespace std::placeholders;
    Point minPtFirst = *std::min_element(first.points.cbegin(), first.points.cend());
    Point minPtSecond = *std::min_element(second.points.cbegin(), second.points.cend());
    Point maxPtFirst = *std::max_element(first.points.cbegin(), first.points.cend());
    Point maxPtSecond = *std::max_element(second.points.cbegin(), second.points.cend());
    return ((maxPtFirst >= minPtSecond) && (minPtFirst <= maxPtSecond))
        || ((maxPtFirst >= minPtSecond) && (minPtFirst <= maxPtSecond));
  }

  double addArea(double currentArea, const Polygon& polygon)
  {
    return currentArea += getArea(polygon);
  }

  double addAreaIf(double currentArea, const Polygon& polygon, std::function< bool(const Polygon&) > pred)
  {
    if (pred(polygon))
    {
      currentArea += getArea(polygon);
    }
    return currentArea;
  }
}
