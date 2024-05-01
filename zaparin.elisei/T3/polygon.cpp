#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include "point.hpp"

std::istream& zaparin::operator>>(std::istream& in, Polygon& plg)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  Point pointTemp{ 0, 0 };
  Polygon plgTemp;
  int pointsCount = 0;
  in >> pointsCount;


  for (int i = 0; (i < pointsCount) && in; i++)
  {
    in >> pointTemp;
    plgTemp.points.push_back(pointTemp);
  }

  if (in)
  {
    plg = plgTemp;
  }

  return in;
}

std::ostream& zaparin::operator<<(std::ostream& out, const Polygon& plg)
{
  using out_it = std::ostream_iterator< Point >;

  std::copy(plg.points.begin(), plg.points.end(), out_it{ out, " " });

  return out;
}

bool zaparin::operator==(const Polygon& plg1, const Polygon& plg2)
{
  return (plg1.points == plg2.points);
}

const zaparin::Point& zaparin::TriangleArea::operator()(const Point& p2, const Point& p3)
{
  double a = getLength(p1, p2);
  double b = getLength(p2, p3);
  double c = getLength(p1, p3);
  double p = (a + b + c) / 2;
  area += std::sqrt(p * (p - a) * (p - b) * (p - c));
  return p3;
}

double zaparin::getArea(const Polygon& plg)
{
  TriangleArea accArea{ 0.0, plg.points[0] };
  std::accumulate(plg.points.begin() + 2, plg.points.end(), plg.points[1], std::ref(accArea));
  return accArea.area;
}

void zaparin::PolygonsArea::operator()(const Polygon& plg)
{
  area += getArea(plg);
}

bool zaparin::isEven(const Polygon& plg)
{
  return ((plg.points.size() % 2) == 0);
}

bool zaparin::isOdd(const Polygon& plg)
{
  return ((plg.points.size() % 2) == 1);
}

bool zaparin::isNov::operator()(const Polygon& plg)
{
  return (nov == plg.points.size());
}

void zaparin::MaxArea::operator()(const Polygon& plg)
{
  double newArea = getArea(plg);
  if (newArea > area)
  {
    area = newArea;
  }
}

void zaparin::MaxVertexes::operator()(const Polygon& plg)
{
  size_t newVertexes = plg.points.size();
  if (newVertexes > vertexes)
  {
    vertexes = newVertexes;
  }
}

void zaparin::MinArea::operator()(const Polygon& plg)
{
  double newArea = getArea(plg);
  if (newArea < area)
  {
    area = newArea;
  }
}

void zaparin::MinVertexes::operator()(const Polygon& plg)
{
  size_t newVertexes = plg.points.size();
  if (newVertexes < vertexes)
  {
    vertexes = newVertexes;
  }
}

