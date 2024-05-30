#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <cmath>
#include "polygon.hpp"

double zaparin::TriangleArea::operator()(const Point& p3)
{
  double a = 0.0, b = 0.0, c = 0.0, p = 0.0;

  a = getLength(p1, p2);
  b = getLength(p2, p3);
  c = getLength(p1, p3);

  p = (a + b + c) / 2;

  p2 = p3;

  return (sqrt(p * (p - a) * (p - b) * (p - c)));
}

double zaparin::getArea(const Polygon& plg)
{
  TriangleArea func{ plg.points[0], plg.points[1] };
  std::vector< double > areas(plg.points.size());

  std::transform(std::begin(plg.points) + 2, std::end(plg.points), areas.begin(), func);

  return std::accumulate(areas.begin(), areas.end(), 0.0, std::plus< double >{});
}

size_t zaparin::getVertexes(const Polygon& plg)
{
  return plg.points.size();
}

bool zaparin::isEven(const Polygon& plg)
{
  return (plg.points.size() % 2 == 0);
}

bool zaparin::isOdd(const Polygon& plg)
{
  return (plg.points.size() % 2 != 0);
}

bool zaparin::isEqualVertexes(size_t numOfVertexes, const Polygon& plg)
{
  return (plg.points.size() == numOfVertexes);
}

size_t zaparin::isEqualCounter(const Polygon& plg, const std::vector< Point >& src, size_t& counter)
{
  if (src == plg.points)
  {
    counter++;
  }
  else
  {
    counter = 0;
  }
  return counter;
}

bool zaparin::isIntersected(const Polygon& plg, const std::vector< Point >& points)
{
  auto minmaxPoint1 = std::minmax_element(plg.points.begin(), plg.points.end());
  auto minmaxPoint2 = std::minmax_element(points.begin(), points.end());

  return (*minmaxPoint1.second >= *minmaxPoint2.first && *minmaxPoint1.first <= *minmaxPoint2.second);
}

void zaparin::cmdArea(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  std::vector< Polygon > tempPolygons;
  std::vector< double > tempAreas;
  size_t numOfVertexes = 0;
  size_t counter = 0;

  std::string parameter;
  in >> parameter;

  using namespace std::placeholders;

  if (parameter == "EVEN")
  {
    counter = count_if(std::begin(plgs), std::end(plgs), isEven);
    tempPolygons.reserve(counter);
    tempAreas.reserve(counter);

    std::copy_if(std::begin(plgs), std::end(plgs), std::back_inserter(tempPolygons), isEven);
  }
  else if (parameter == "ODD")
  {
    counter = count_if(std::begin(plgs), std::end(plgs), isOdd);
    tempPolygons.reserve(counter);
    tempAreas.reserve(counter);

    std::copy_if(std::begin(plgs), std::end(plgs), std::back_inserter(tempPolygons), isOdd);
  }
  else if (parameter == "MEAN")
  {
    if (plgs.size() == 0)
    {
      throw std::logic_error("ZERO POLYGONS");
    }

    std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(tempAreas), getArea);

    out << std::fixed;
    out.precision(1);
    out << (std::accumulate(tempAreas.begin(), tempAreas.end(), 0.0, std::plus< double >{}) / plgs.size()) << "\n";

    return;
  }
  else
  {
    numOfVertexes = std::stoull(parameter);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("TOO LOW VERTEXES");
    }
    else
    {
      counter = count_if(std::begin(plgs), std::end(plgs), std::bind(isEqualVertexes, numOfVertexes, _1));
      tempPolygons.reserve(counter);
      tempAreas.reserve(counter);

      using namespace std::placeholders;
      std::copy_if(std::begin(plgs), std::end(plgs), std::back_inserter(tempPolygons), std::bind(isEqualVertexes, numOfVertexes, _1));
    }
  }

  std::transform(std::begin(tempPolygons), std::end(tempPolygons), std::back_inserter(tempAreas), getArea);

  out << std::fixed;
  out.precision(1);
  out << std::accumulate(tempAreas.begin(), tempAreas.end(), 0.0, std::plus< double >{}) << "\n";
}

void zaparin::cmdMax(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  if (plgs.size() == 0)
  {
    throw std::logic_error("ZERO POLYGONS");
  }
  else
  {
    std::string parameter;
    in >> parameter;

    if (parameter == "AREA")
    {
      std::vector< double > temp(plgs.size());

      std::transform(std::begin(plgs), std::end(plgs), temp.begin(), getArea);

      auto max_iter = std::max_element(temp.begin(), temp.end());
      out << std::fixed;
      out.precision(1);
      out << *max_iter << "\n";
    }
    else if (parameter == "VERTEXES")
    {
      std::vector< size_t > temp(plgs.size());

      std::transform(std::begin(plgs), std::end(plgs), temp.begin(), getVertexes);

      auto max_iter = std::max_element(temp.begin(), temp.end());
      out << *max_iter << "\n";
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }
}

void zaparin::cmdMin(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  if (plgs.size() == 0)
  {
    throw std::logic_error("ZERO POLYGONS");
  }
  else
  {
    std::string parameter;
    in >> parameter;

    if (parameter == "AREA")
    {
      std::vector< double > temp(plgs.size());

      std::transform(std::begin(plgs), std::end(plgs), temp.begin(), getArea);

      auto min_iter = std::min_element(temp.begin(), temp.end());
      out << std::fixed;
      out.precision(1);
      out << *min_iter << "\n";
    }
    else if (parameter == "VERTEXES")
    {
      std::vector< size_t > temp(plgs.size());

      std::transform(std::begin(plgs), std::end(plgs), temp.begin(), getVertexes);

      auto min_iter = std::min_element(temp.begin(), temp.end());
      out << *min_iter << "\n";
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }
}

void zaparin::cmdCount(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  size_t numOfVertexes = 0;

  std::string parameter;
  in >> parameter;

  using namespace std::placeholders;
  if (parameter == "EVEN")
  {
    out << std::count_if(plgs.begin(), plgs.end(), isEven) << "\n";
  }
  else if (parameter == "ODD")
  {
    out << std::count_if(plgs.begin(), plgs.end(), isOdd) << "\n";
  }
  else
  {
    numOfVertexes = std::stoull(parameter);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("TOO LOW VERTEXES");
    }
    else
    {
      using namespace std::placeholders;
      out << std::count_if(plgs.begin(), plgs.end(), std::bind(isEqualVertexes, numOfVertexes, _1)) << "\n";
    }
  }
}

void zaparin::cmdMaxSeq(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  size_t numOfVertexes = 0, counter = 0;
  std::vector< Point > srcPoints;
  std::vector< size_t > sequences;

  using in_it = std::istream_iterator< Point >;
  in >> numOfVertexes;

  if (numOfVertexes < 3)
  {
    throw std::logic_error("TOO LOW VERTEXES");
  }

  srcPoints.reserve(numOfVertexes);
  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(srcPoints));

  if (srcPoints.empty() || in.peek() != '\n')
  {
    throw std::logic_error("WRONG NUM OF VERTEXES");
  }

  sequences.reserve(plgs.size());

  using namespace std::placeholders;
  auto functor = std::bind(isEqualCounter, _1, srcPoints, counter);
  std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(sequences), functor);

  auto max_iter = std::max_element(sequences.begin(), sequences.end());
  out << *max_iter << "\n";
}

void zaparin::cmdIntersections(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  size_t numOfVertexes = 0;
  std::vector< Point > temp;

  using in_it = std::istream_iterator< Point >;
  in >> numOfVertexes;

  if (numOfVertexes < 3)
  {
    throw std::logic_error("TOO LOW VERTEXES");
  }

  temp.reserve(numOfVertexes);
  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(temp));

  if (temp.empty() || in.peek() != '\n')
  {
    throw std::logic_error("WRONG NUM OF VERTEXES");
  }

  using namespace std::placeholders;
  auto functor = std::bind(isIntersected, _1, temp);

  out << std::count_if(plgs.begin(), plgs.end(), functor) << "\n";
}

