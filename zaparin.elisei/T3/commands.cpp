#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <cmath>
#include "polygon.hpp"

double zaparin::getArea(const Polygon& plg)
{
  Point p1 = plg.points[0], p2, p3;
  double area = 0.0, a, b, c, p;
  size_t size = plg.points.size();

  for (size_t i = 1; i < size - 1; i++)
  {
    p2 = plg.points[i];
    p3 = plg.points[i + 1];

    a = getLength(p1, p2);
    b = getLength(p2, p3);
    c = getLength(p1, p3);

    p = (a + b + c) / 2;

    area += sqrt(p * (p - a) * (p - b) * (p - c));
  }

  return area;
}

double zaparin::getSpecificArea(const Polygon& plg, Type type, size_t vertexes, size_t polygons)
{
  double area = 0.0;
  if (type == Even)
  {
    if (plg.points.size() % 2 == 0)
    {
      area += getArea(plg);
    }
  }
  if (type == Odd)
  {
    if (plg.points.size() % 2 != 0)
    {
      area += getArea(plg);
    }
  }
  if (type == Mean)
  {
    area += (getArea(plg) / polygons);
  }
  if (type == Vertexes)
  {
    if (plg.points.size() == vertexes)
    {
      area += getArea(plg);
    }
  }

  return area;
}

size_t zaparin::getVertexes(const Polygon& plg)
{
  return plg.points.size();
}

bool zaparin::isRight(const Polygon& plg, Type type, size_t vertexes)
{
  if (type == Even)
  {
    return (plg.points.size() % 2 == 0);
  }
  else if (type == Odd)
  {
    return (plg.points.size() % 2 != 0);
  }
  else if (type == Vertexes)
  {
    return (plg.points.size() == vertexes);
  }
  else
  {
    return 0;
  }
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
  std::function< double(Polygon) > functor;
  std::vector< double > temp;
  size_t numOfVertexes;

  std::string parameter;
  in >> parameter;

  using namespace std::placeholders;

  if (parameter == "EVEN")
  {
    functor = std::bind(getSpecificArea, _1, Even, 0, 0);
  }
  else if (parameter == "ODD")
  {
    functor = std::bind(getSpecificArea, _1, Odd, 0, 0);
  }
  else if (parameter == "MEAN")
  {
    if (plgs.size() == 0)
    {
      throw std::logic_error("ZERO POLYGONS");
    }

    functor = std::bind(getSpecificArea, _1, Mean, 0, plgs.size());
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
      functor = std::bind(getSpecificArea, _1, Vertexes, std::stoull(parameter), 0);
    }
  }

  std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), functor);

  out << std::fixed;
  out.precision(1);
  out << std::accumulate(temp.begin(), temp.end(), 0.0, std::plus< double >{}) << "\n";
}

void zaparin::cmdMax(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  if (plgs.size() == 0)
  {
    throw std::logic_error("ZERO POLYGONS");
  }
  else
  {
    std::vector< double > temp;

    std::string parameter;
    in >> parameter;

    if (parameter == "AREA")
    {
      std::vector< double > temp;

      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getArea);

      auto max_iter = std::max_element(temp.begin(), temp.end());
      out << std::fixed;
      out.precision(1);
      out << *max_iter << "\n";
    }
    else if (parameter == "VERTEXES")
    {
      std::vector< size_t > temp;

      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getVertexes);

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
    std::vector< double > temp;

    std::string parameter;
    in >> parameter;

    if (parameter == "AREA")
    {
      std::vector< double > temp;

      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getArea);

      auto min_iter = std::min_element(temp.begin(), temp.end());
      out << std::fixed;
      out.precision(1);
      out << *min_iter << "\n";
    }
    else if (parameter == "VERTEXES")
    {
      std::vector< size_t > temp;

      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getVertexes);

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
  std::function< bool(Polygon) > functor;
  size_t numOfVertexes = 0;

  std::string parameter;
  in >> parameter;

  using namespace std::placeholders;
  if (parameter == "EVEN")
  {
    functor = std::bind(isRight, _1, Even, 0);
  }
  else if (parameter == "ODD")
  {
    functor = std::bind(isRight, _1, Odd, 0);
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
      functor = std::bind(isRight, _1, Vertexes, numOfVertexes);
    }
  }

  out << std::count_if(plgs.begin(), plgs.end(), functor) << "\n";
}

void zaparin::cmdMaxSeq(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  size_t numOfVertexes = 0, counter = 0;
  std::vector< Point > srcPoints;
  std::vector< size_t > sequences;

  using in_it = std::istream_iterator< Point >;
  in >> numOfVertexes;
  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(srcPoints));

  if (srcPoints.empty() || in.peek() != '\n')
  {
    throw std::logic_error("WRONG NUM OF VERTEXES");
  }

  using namespace std::placeholders;
  auto functor = std::bind(isEqualCounter, _1, srcPoints, counter);
  std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(sequences), functor);

  auto max_iter = std::max_element(sequences.begin(), sequences.end());
  out << *max_iter << "\n";
}

void zaparin::cmdIntersections(std::vector< Polygon > plgs, std::istream& in, std::ostream& out)
{
  size_t numOfVertexes = 0;
  std::vector< Point > temp;

  using in_it = std::istream_iterator< Point >;
  in >> numOfVertexes;
  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(temp));

  if (temp.empty() || in.peek() != '\n')
  {
    throw std::logic_error("WRONG NUM OF VERTEXES");
  }

  using namespace std::placeholders;
  auto functor = std::bind(isIntersected, _1, temp);

  out << std::count_if(plgs.begin(), plgs.end(), functor) << "\n";
}

