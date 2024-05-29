#include "Polygon.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <Delimeter.hpp>

std::istream& yakshieva::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = yakshieva::DelimeterIO;
  int x = 0;
  int y = 0;
  in >> del{ '(' } >> x >> del{ ';' } >> y >> del{ ')' };
  if (in)
  {
    point = Point{ x, y };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& yakshieva::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool yakshieva::operator==(const Point& p1, const Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

std::istream& yakshieva::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexCount = 0;
  in >> vertexCount;
  if (vertexCount < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector< Point > vertexBuffer(vertexCount);
  vertexBuffer.reserve(vertexCount);
  using input_iterator_t = std::istream_iterator< Point >;
  std::copy_n(input_iterator_t{ in }, vertexCount, vertexBuffer.begin());
  if (in && vertexBuffer.size() == vertexCount)
  {
    polygon.points = std::move(vertexBuffer);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool yakshieva::operator==(const Polygon& p1, const Polygon& p2)
{
  return p1.points == p2.points;
}

bool yakshieva::isVertexEven(const Polygon& polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool yakshieva::isVertexOdd(const Polygon& polygon)
{
  return !isVertexEven(polygon);
}

bool yakshieva::hasNumOfVertices(const Polygon& polygon, size_t numOfVertices)
{
  return polygon.points.size() == numOfVertices;
}
