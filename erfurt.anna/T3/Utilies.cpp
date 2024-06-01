#include "Utilies.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <cmath>
#include <iomanip>
#include "StreamGuard.hpp"

namespace erfurt
{
  template < class UnaryPredicate >
  double getAreaIf(const std::vector< Polygon > & poly, UnaryPredicate pred)
  {
    std::vector< Polygon > polygon;
    polygon.reserve(poly.size());
    std::copy_if(poly.cbegin(), poly.cend(), std::back_inserter(polygon), pred);
    return getAreaPolygons(polygon);
  }

  double areaNum(const std::vector< Polygon > & poly, size_t num)
  {
    return getAreaIf(poly, std::bind(isNumVertexes, std::placeholders::_1, num));
  }

  double areaEven(const std::vector< Polygon > & poly)
  {
    return getAreaIf(poly, isEvenVertexes);
  }

  double areaOdd(const std::vector< Polygon > & poly)
  {
    return getAreaIf(poly, isOddVertexes);
  }

  double areaMean(const std::vector< Polygon > & poly)
  {
    if (poly.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return (getAreaPolygons(poly) / poly.size());
  }

  bool isLessArea(const Polygon & poly1, const Polygon & poly2);
  bool isLessSize(const Polygon & poly1, const Polygon & poly2);

  void maxArea(const std::vector< Polygon > & poly, std::ostream & out)
  {
    auto max_elem = std::max_element(poly.cbegin(), poly.cend(), isLessArea);
    if (max_elem == poly.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    StreamGuard sg(out);
    out << std::fixed;
    out.precision(1);
    out << getArea(*max_elem);
  }

  void maxVertexes(const std::vector< Polygon > & poly, std::ostream & out)
  {
    auto max_elem = std::max_element(poly.cbegin(), poly.cend(), isLessSize);
    if (max_elem == poly.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << max_elem->points.size();
  }

  void minArea(const std::vector< Polygon > & poly, std::ostream & out)
  {
    auto min_elem = std::min_element(poly.cbegin(), poly.cend(), isLessArea);
    if (min_elem == poly.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    StreamGuard sg(out);
    out << std::fixed;
    out.precision(1);
    out << getArea(*min_elem);
  }

  void minVertexes(const std::vector< Polygon > & poly, std::ostream & out)
  {
    auto min_elem = std::min_element(poly.cbegin(), poly.cend(), isLessSize);
    if (min_elem == poly.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << min_elem->points.size();
  }

  bool isEvenVertexes(const Polygon & poly)
  {
    return (poly.points.size() % 2 == 0);
  }

  bool isOddVertexes(const Polygon & poly)
  {
    return !isEvenVertexes(poly);
  }

  bool isNumVertexes(const Polygon & poly, size_t num)
  {
    return (poly.points.size() == num);
  }

  bool isLessArea(const Polygon & poly1, const Polygon & poly2)
  {
    return (getArea(poly1) < getArea(poly2));
  }

  bool isLessSize(const Polygon & poly1, const Polygon & poly2)
  {
    return (poly1.points.size() < poly2.points.size());
  }

  bool isPerm(const Polygon & poly1, const Polygon & poly2)
  {
    if (poly1.points.size() != poly2.points.size())
    {
      return false;
    }
    auto pred = std::bind(isPointIn, std::placeholders::_1, poly2);
    return std::distance(poly1.points.cbegin(), poly1.points.cend()) ==
      std::count_if(poly1.points.cbegin(), poly1.points.cend(), pred);
  }

  bool isIndenticalPoly(const Polygon & poly1, const Polygon & poly2, const Polygon & poly)
  {
    return isEqual(poly1, poly) && isEqual(poly2, poly);
  }
}

