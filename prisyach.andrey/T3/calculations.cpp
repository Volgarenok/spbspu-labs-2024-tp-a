#include "calculations.hpp"
#include <functional>
#include <iosfwd>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <algorithm>
#include "streamguard.hpp"
#include "geometric.hpp"

namespace detail
{
  double countArea(double area, const prisyach::Polygon & polygon)
  {
    return area + prisyach::getArea(polygon);
  }
  bool even(const prisyach::Polygon & p)
  {
    return (p.points.size() > 2) && (p.points.size() % 2 == 0);
  }
  bool odd(const prisyach::Polygon & p)
  {
    return (p.points.size() > 2) && (p.points.size() % 2 != 0);
  }
  bool isSize(const prisyach::Polygon & p, size_t size)
  {
    return p.points.size() == size;
  }
  bool equalPoint(const prisyach::Point & p1, const prisyach::Point & p2)
  {
    return (p1.x_ == p2.x_) && (p1.y_ == p2.y_);
  }
  bool isPerm(const prisyach::Polygon & p1, const prisyach::Polygon & p2)
  {
    return (p1.points.size() == p2.points.size()) && (std::is_permutation(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin(),
    p2.points.cend(), equalPoint));
  }
  bool areSame(const prisyach::Polygon & p1, const prisyach::Polygon & p2, const prisyach::Polygon & p3)
  {
    return (p1.points.size() == p2.points.size()) && std::equal(p1.points.begin(), p1.points.end(), p2.points.begin())
     && std::equal(p1.points.begin(), p1.points.end(), p3.points.begin());
  }
}

void prisyach::doArea(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string argument = "";
  in >> argument;
  std::vector< Polygon > shapes;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::inserter(shapes, shapes.end()), detail::even);
    std::vector< double > areas;
    std::transform(shapes.cbegin(), shapes.cend(), std::inserter(areas, areas.end()), getArea);
    out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
  else if (argument == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::inserter(shapes, shapes.end()), detail::odd);
    std::vector< double > areas;
    std::transform(shapes.cbegin(), shapes.cend(), std::inserter(areas, areas.end()), getArea);
    out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
  else if (argument ==  "MEAN")
  {
    if (polygons.empty())
    {
      throw std::logic_error("Zero shapes");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::inserter(shapes, shapes.end()));
    std::vector< double > areas;
    std::transform(shapes.cbegin(), shapes.cend(), std::inserter(areas, areas.end()), getArea);
    out << std::accumulate(areas.cbegin(), areas.cend(), 0.0) / polygons.size();
  }
  else
  {
    size_t pointsCount = std::stoull(argument);
    if (pointsCount < 3)
    {
      throw std::logic_error("Wrong number of points");
    }
    auto isRightCount = std::bind(detail::isSize, _1, pointsCount);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::inserter(shapes, shapes.end()), isRightCount);
    std::vector< double > areas;
    std::transform(shapes.cbegin(), shapes.cend(), std::inserter(areas, areas.end()), getArea);
    out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
}

void prisyach::doMax(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument = "";
  in >> argument;
  if (polygons.empty()){
    throw std::logic_error("Zero polygons");
  }
  if (argument == "AREA")
  {
    StreamGuard guard(in);
    out << std::setprecision(1) << std::fixed;
    out << getArea(*std::max_element(polygons.begin(), polygons.end(), [](Polygon p1, Polygon p2){
      return getArea(p1) < getArea(p2);
    }));
  }
  else if (argument == "VERTEXES")
  {
    out << std::max_element(polygons.begin(), polygons.end(), [](Polygon p1, Polygon p2){
      return p1.points.size() < p2.points.size();
    })->points.size();
  }
  else
  {
    throw std::logic_error("Wrong parameter");
  }
}

void prisyach::doMin(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument = "";
  in >> argument;
  if (polygons.empty()){
    throw std::logic_error("Zero polygons");
  }
  if (argument == "AREA")
  {
    StreamGuard guard(in);
    out << std::setprecision(1) << std::fixed;
    out << getArea(*std::min_element(polygons.begin(), polygons.end(), [](Polygon p1, Polygon p2){
      return getArea(p1) < getArea(p2);
    }));
  }
  else if (argument == "VERTEXES")
  {
    out << std::min_element(polygons.begin(), polygons.end(), [](Polygon p1, Polygon p2){
      return p1.points.size() < p2.points.size();
    })->points.size();
  }
  else
  {
    throw std::logic_error("Wrong parameter");
  }
}

void prisyach::doCount(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string argument = "";
  in >> argument;
  if (argument == "EVEN")
  {
    out << std::count_if(polygons.begin(), polygons.end(), detail::even);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(polygons.begin(), polygons.end(), detail::odd);
  }
  else
  {
    size_t pointsCount = std::stoull(argument);
    if (pointsCount < 3)
    {
      throw std::logic_error("Wrong count");
    }
    auto isRightCount = std::bind(detail::isSize, std::placeholders::_1, pointsCount);
    out << std::count_if(polygons.begin(), polygons.end(), isRightCount);
  }
}

void prisyach::doPerms(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon p;
  in >> p;
  if (!in || p.points.empty())
  {
    throw std::invalid_argument("Wrong input");
  }
  else
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(detail::isPerm, p, std::placeholders::_1));
  }
}

namespace detail
{
  struct Counter
  {
    size_t counter = 0;
    size_t operator()(const prisyach::Polygon & p1, const prisyach::Polygon & p2);
  };
}

size_t detail::Counter::operator()(const prisyach::Polygon & p1, const prisyach::Polygon & p2)
{
  if (p1 == p2)
  {
    return ++counter;
  }
  counter = 0;
  return counter;
}

void prisyach::doMaxSeq(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon p;
  in >> p;
  if (!in || p.points.empty())
  {
    throw std::invalid_argument("Wrong input");
  }
  else
  {
    std::vector< size_t > results;
    detail::Counter counter;
    std::transform(polygons.begin(), polygons.end(), std::inserter(results, results.end()), std::bind(counter, std::placeholders::_1, p));
    out <<  *(std::max_element(results.begin(), results.end()));
  }
}

void prisyach::doRmEcho(std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  Polygon p;
  in >> p;
  if (!in || p.points.empty())
  {
    throw std::logic_error("Wrong input");
  }
  auto it = std::unique(polygons.begin(), polygons.end(),
    std::bind(detail::areSame, std::placeholders::_1, std::placeholders::_2, p));
  size_t erased = std::distance(it, polygons.end());
  out << erased;
  polygons.erase(it, polygons.end());
}
