#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <iomanip>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

#include <scopeGuard.hpp>

namespace kozlova
{
  void generalArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    double sum = 0.0;
    std::map< std::string, std::function< double() > > area;
    {
      area["EVEN"] = std::bind(getAreaEven, polygons);
      area["ODD"] = std::bind(getAreaOdd, polygons);
      area["MEAN"] = std::bind(getAreaMean, polygons);
    }
    std::string arg;
    in >> arg;
    if (arg == "MEAN" || arg == "ODD" || arg == "EVEN")
    {
      if (polygons.empty() && arg == "MEAN")
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      sum = area[arg]();
    }
    else
    {
      size_t number = std::stoull(arg);
      if (number < 3)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      sum = getAreaNum(polygons, number);
    }
    ScopeGuard scopeGuard(out);
    out << std::fixed << std::setprecision(1) << sum << '\n';
  }

  template < typename PredicateOneVariable >
  double getAreaIf(const std::vector< Polygon >& polygons, PredicateOneVariable predicate)
  {
    std::vector< Polygon > select;
    select.reserve(polygons.size());
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(select), predicate);
    return getAreaPolygons(select);
  }

  bool isEven(const Polygon& polygon)
  {
    return (polygon.points.size() % 2 == 0);
  }

  bool isOdd(const Polygon& polygon)
  {
    return (polygon.points.size() % 2 != 0);
  }

  double getAreaEven(const std::vector< Polygon >& polygons)
  {
    return getAreaIf(polygons, isEven);
  }

  double getAreaOdd(const std::vector< Polygon >& polygons)
  {
    return getAreaIf(polygons, isOdd);
  }

  double getAreaMean(const std::vector< Polygon >& polygons)
  {
    return (getAreaPolygons(polygons) / polygons.size());
  }

  bool isNum(const Polygon& polygon, size_t number)
  {
    return number == polygon.points.size();
  }

  double getAreaNum(const std::vector< Polygon >& polygons, size_t number)
  {
    using namespace std::placeholders;
    return getAreaIf(polygons, std::bind(isNum, _1, number));
  }

  void generalMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::map< std::string, std::function< double() > > maxArea;
    {
      maxArea["AREA"] = std::bind(getAreaMax, polygons);
    }

    std::map< std::string, std::function< size_t() > > maxVertexes;
    {
      maxVertexes["VERTEXES"] = std::bind(getVertexesMax, polygons);
    }

    std::string arg;
    in >> arg;
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (arg == "VERTEXES")
    {
      out << maxVertexes[arg]() << '\n';
    }
    else
    {
      ScopeGuard scopeGuard(out);
      out << std::fixed << std::setprecision(1);
      out << maxArea[arg]() << '\n';
    }
  }

  double getAreaMax(const std::vector< Polygon >& polygons)
  {
    std::vector< double > area;
    area.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
    auto max = std::max_element(area.cbegin(), area.cend());
    if (max == area.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return *max;
  }

  size_t getVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  size_t getVertexesMax(const std::vector< Polygon >& polygons)
  {
    std::vector< double > vertexes;
    vertexes.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(vertexes), getVertexes);
    auto max = std::max_element(vertexes.cbegin(), vertexes.cend());
    if (max == vertexes.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return *max;
  }

  void generalMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::map< std::string, std::function< double() > > minArea;
    {
      minArea["AREA"] = std::bind(getAreaMin, polygons);
    }

    std::map< std::string, std::function< size_t() > > minVertexes;
    {
      minVertexes["VERTEXES"] = std::bind(getVertexesMin, polygons);
    }

    std::string arg;
    in >> arg;
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (arg == "VERTEXES")
    {
      out << minVertexes[arg]() << '\n';
    }
    else
    {
      ScopeGuard scopeGuard(out);
      out << std::fixed << std::setprecision(1);
      out << minArea[arg]() << '\n';
    }
  }

  double getAreaMin(const std::vector< Polygon >& polygons)
  {
    std::vector< double > area;
    area.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
    auto min = std::min_element(area.cbegin(), area.cend());
    if (min == area.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return *min;
  }

  size_t getVertexesMin(const std::vector< Polygon >& polygons)
  {
    std::vector< double > vertexes;
    vertexes.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(vertexes), getVertexes);
    auto min = std::min_element(vertexes.cbegin(), vertexes.cend());
    if (min == vertexes.cend())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return *min;
  }

  void generalCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::map< std::string, std::function< size_t() > > count;
    {
      count["EVEN"] = std::bind(getCountEven, polygons);
      count["ODD"] = std::bind(getCountOdd, polygons);
    }
    std::string arg;
    in >> arg;
    if (arg == "EVEN" || arg == "ODD")
    {
      out << count[arg]() << '\n';
    }
    else
    {
      size_t num = std::stoull(arg);
      if (num < 3)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      size_t res = getCountNum(polygons, num);
      out << res << "\n";
    }
  }

  size_t getCountEven(const std::vector< Polygon >& polygons)
  {
    return std::count_if(polygons.cbegin(), polygons.cend(), isEven);
  }

  size_t getCountOdd(const std::vector< Polygon >& polygons)
  {
    return std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }

  size_t getCountNum(const std::vector< Polygon >& polygons, size_t number)
  {
    using namespace std::placeholders;
    return std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isNum, _1, number));
  }

  bool isEqual(const Point& point1, const Point& point2)
  {
    return point1 == point2;
  }

  bool isPoint(const Point& point, const Polygon& polygon)
  {
    Point sample = point;
    auto pred1 = std::bind(isEqual, std::placeholders::_1, sample);
    auto it_forward = std::find_if(polygon.points.cbegin(), polygon.points.cend(), pred1);
    Point inverted({ point.y, point.x });
    auto pred2 = std::bind(isEqual, std::placeholders::_1, inverted);
    auto it_reverse = std::find_if(polygon.points.cbegin(), polygon.points.cend(), pred2);
    return it_forward != polygon.points.cend() || it_reverse != polygon.points.cend();
  }

  bool isPerms(const Polygon& polygon, const Polygon& sample)
  {
    if (polygon.points.size() != sample.points.size())
    {
      return false;
    }
    using namespace std::placeholders;
    auto pred = std::bind(isPoint, _1, sample);
    size_t count = std::count_if(polygon.points.cbegin(), polygon.points.cend(), pred);
    size_t num = std::distance(polygon.points.cbegin(), polygon.points.cend());
    return count == num;
  }

  void generalPerms(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    Polygon sample;
    in >> sample;
    if (!in || in.peek() != '\n' || sample.points.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    auto pred = std::bind(isPerms, _1, sample);
    size_t count = std::count_if(polygons.cbegin(), polygons.cend(), pred);
    out << count << '\n';
  }

  bool isIdentical(const Polygon& polygon1, const Polygon& polygon2, const Polygon& sample)
  {
    return (polygon1 == polygon2) && (polygon1 == sample);
  }

  void generalRmEcho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    Polygon sample;
    in >> sample;
    if (!in ||  sample.points.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    auto pred = std::bind(isIdentical, _1, _2, sample);
    auto polynew = std::unique(polygons.begin(), polygons.end(), pred);
    size_t distance = std::distance(polynew, polygons.end());
    polygons.resize(std::distance(polygons.begin(), polynew));
    out << distance << '\n';
  }

  struct RightAngle
  {
    Point p1;
    Point p2;

    bool operator()(const Point& p3)
    {
      bool factor = (p3.x - p2.x) * (p1.x - p2.x) + (p3.y - p2.y) * (p1.y - p2.y);
      p1 = p2;
      p2 = p3;
      return factor == 0;
    }
  };

  bool isRightAngle(const Polygon& polygon)
  {
    auto right_func = RightAngle{ *(polygon.points.end() - 2), *(polygon.points.end() - 1) };
    return std::any_of(polygon.points.cbegin(), polygon.points.cend(), right_func);
  }

  void generalRightShapes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isRightAngle) << '\n';
  }
}
