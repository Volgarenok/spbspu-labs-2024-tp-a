#include "triangle.hpp"

#include <cmath>

double rebdev::Triangle::getArea() const noexcept
{
  double area = pointArr[0].x * (pointArr[1].y - pointArr[2].y);
  area += pointArr[1].x * (pointArr[2].y - pointArr[0].y);
  area += pointArr[2].x * (pointArr[0].y - pointArr[1].y);
  area /= 2;
  return std::abs(area);
}
rebdev::TriangleGenerator::TriangleGenerator(const Polygon & p) noexcept:
  safedPoly(p),
  pointNow(1)
{}
rebdev::Triangle rebdev::TriangleGenerator::operator()() noexcept
{
  Triangle trio;
  trio.pointArr[0] = safedPoly.points[0];
  trio.pointArr[1] = safedPoly.points[pointNow];
  trio.pointArr[2] = safedPoly.points[++pointNow];

  return trio;
}

double rebdev::plusArea(double areaNow, const Triangle & tria) noexcept
{
  return (areaNow + tria.getArea());
}
