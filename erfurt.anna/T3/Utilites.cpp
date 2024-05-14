#include "Utilites.hpp"
#include <functional>
#include <algorithm>
#include "Polygon.hpp"

namespace erfurt
{
  double AccAreaEvenOdd::operator()(double sum, const Polygon & poly)
  {
    if ((parameter == "ODD" && (poly.points.size() % 2) == 1) || (parameter == "EVEN" && (poly.points.size() % 2) == 0))
    {
      return sum + getArea(poly);
    }
    return sum;
  }

  double AccAreaVertexes::operator()(double sum, const Polygon & poly)
  {
    if (poly.points.size() == numOfVertexes)
    {
      return sum + getArea(poly);
    }
    return sum;
  }

  double AccAreaMean::operator()(double sum, const Polygon & poly)
  {
    return sum + getArea(poly) / count;
  }

  bool isPerm(const Polygon & poly1, const Polygon & poly2)
  {
    if (poly1.points.size() != poly2.points.size())
    {
      return false;
    }
    auto perm = std::bind(isPointConsist, std::placeholders::_1, poly2);
    return std::distance(poly2.points.cbegin(), poly2.points.cend()) == std::count_if(poly1.points.cbegin(), poly1.points.cend(), perm);
  }

  double erfurt::AccumulatePolygonArea::operator()(double area, const Point & p1, const Point & p2)
  {
    area += 0.5 * std::abs((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
    p0 = p1;
    return area;
  }

  bool IdenticalPoly::operator()(const Polygon & p1, const Polygon & p2)
  {
    return isEqual(p1, p2) && isEqual(poly, p1);
  }
}