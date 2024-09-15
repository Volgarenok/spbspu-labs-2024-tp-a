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


#include "scopeGuard.hpp"

namespace kozlova
{
  void generalArea(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    double sum = 0.0;
    std::map<std::string, std::function< double() >> area;
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
        throw std::logic_error(" <INVALID COMMAND> ");
      }
      sum = area[arg]();
    }
    else
    {
      size_t number = std::stoull(arg);
      if (number < 3)
      {
        throw std::logic_error(" <INVALID COMMAND> ");
      }
      sum = getAreaNum(polygons, number);
    }
    ScopeGuard scopeGuard(out);
    out << std::fixed << std::setprecision(1) << sum << '\n';
  }


  template <typename PredicateOneVariable>
  double getAreaIf(const std::vector<Polygon>& polygons, PredicateOneVariable predicate)
  {
    std::vector<Polygon> select;
    select.reserve(polygons.size());
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(select), predicate);
    return getAreaPolygons(select);
  }


  bool isEven(const Polygon& polygon)
  {
    return (polygon.points.size() % 2 != 0);
  }


  bool isOdd(const Polygon& polygon)
  {
    return (polygon.points.size() % 2 == 0);
  }


  double getAreaEven(const std::vector<Polygon>& polygons)
  {
    return getAreaIf(polygons, isEven);
  }


  double getAreaOdd(const std::vector<Polygon>& polygons)
  {
    return getAreaIf(polygons, isOdd);
  }


  double getAreaMean(const std::vector<Polygon>& polygons)
  {
    return (getAreaPolygons(polygons) / polygons.size());
  }


  bool isNum(const Polygon& polygon, size_t number)
  {
    return number == polygon.points.size();
  }


  double getAreaNum(const std::vector<Polygon>& polygons, size_t number)
  {
    using namespace std::placeholders;
    return getAreaIf(polygons, std::bind(isNum, _1, number));
  }


  void generalMax(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    std::map<std::string, std::function< double() >> maxArea;
    {
      maxArea["AREA"] = std::bind(getAreaMax, polygons);
    }

    std::map<std::string, std::function< size_t() >> maxVertexes;
    {
      maxVertexes["VERTEXES"] = std::bind(getVertexesMax, polygons);
    }

    std::string arg;
    in >> arg;
    if (polygons.empty())
    {
      throw std::logic_error(" <INVALID COMMAND> ");
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


  double getAreaMax(const std::vector<Polygon>& polygons)
  {
    std::vector< double > area;
    area.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
    auto max = std::max_element(area.cbegin(), area.cend());
    if (max == area.cend())
    {
      throw std::logic_error(" <INVALID COMMAND> ");
    }
    return *max;
  }

  size_t getVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }


  size_t getVertexesMax(const std::vector<Polygon>& polygons)
  {
    std::vector< double > vertexes;
    vertexes.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(vertexes), getVertexes);
    auto max = std::max_element(vertexes.cbegin(), vertexes.cend());
    if (max == vertexes.cend())
    {
      throw std::logic_error(" <INVALID COMMAND> ");
    }
    return *max;
  }


  void generalMin(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    std::map<std::string, std::function< double() >> minArea;
    {
      minArea["AREA"] = std::bind(getAreaMin, polygons);
    }

    std::map<std::string, std::function< size_t() >> minVertexes;
    {
      minVertexes["VERTEXES"] = std::bind(getVertexesMin, polygons);
    }

    std::string arg;
    in >> arg;
    if (polygons.empty())
    {
      throw std::logic_error(" <INVALID COMMAND> ");
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


  double getAreaMin(const std::vector<Polygon>& polygons)
  {
    std::vector< double > area;
    area.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inse>    
    auto min = std::min_element(area.cbegin(), area.cend());
    if (min == area.cend())
    {
      throw std::logic_error(" <INVALID COMMAND> ");
    }
    return *min;
  }


  size_t getVertexesMin(const std::vector<Polygon>& polygons)
  {
    std::vector< double > vertexes;
    vertexes.reserve(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inse>    
    auto min = std::min_element(vertexes.cbegin(), vertexes.cend());
    if (min == vertexes.cend())
    {
      throw std::logic_error(" <INVALID COMMAND> ");
    }
    return *min;
  }
}
