#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
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
  if (type == Odd)
  {
    return (plg.points.size() % 2 != 0);
  }
  if (type == Vertexes)
  {
    return (plg.points.size() == vertexes);
  }
}

void zaparin::cmdArea(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  std::vector< double > temp;
  std::string parameter;
  in >> parameter;

  using namespace std::placeholders;

  if (parameter == "EVEN")
  {
    auto functor = std::bind(getSpecificArea, _1, Even, 0, 0);
    std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), functor);
  }
  else if (parameter == "ODD")
  {
    auto functor = std::bind(getSpecificArea, _1, Odd, 0, 0);
    std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), functor);
  }
  else if (parameter == "MEAN")
  {
    if (plgs.size() == 0)
    {
      throw InvalidCommand();
    }

    auto functor = std::bind(getSpecificArea, _1, Mean, 0, plgs.size());
    std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), functor);
  }
  else
  {
    auto functor = std::bind(getSpecificArea, _1, Vertexes, std::stoull(parameter), 0);
    std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), functor);
  }

  out << std::fixed;
  out.precision(1);
  out << std::accumulate(temp.begin(), temp.end(), 0.0, std::plus< double >{}) << "\n";
}

void zaparin::cmdMax(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  if (plgs.size() == 0)
  {
    throw InvalidCommand();
  }
  else
  {
    std::vector< double > temp;
    std::string parameter;
    in >> parameter;

    using namespace std::placeholders;
    if (parameter == "AREA")
    {
      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getArea);
      out << std::fixed;
      out.precision(1);
    }
    else if (parameter == "VERTEXES")
    {
      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getVertexes);
    }
    else
    {
      throw InvalidCommand();
    }

    std::sort(temp.begin(), temp.end());
    out << temp[temp.size() - 1] << "\n";
  }
}

void zaparin::cmdMin(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  if (plgs.size() == 0)
  {
    throw InvalidCommand();
  }
  else
  {
    std::vector< double > temp;
    std::string parameter;
    in >> parameter;

    using namespace std::placeholders;
    if (parameter == "AREA")
    {
      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getArea);
      out << std::fixed;
      out.precision(1);
    }
    else if (parameter == "VERTEXES")
    {
      std::transform(std::begin(plgs), std::end(plgs), std::back_inserter(temp), getVertexes);
    }
    else
    {
      throw InvalidCommand();
    }

    std::sort(temp.begin(), temp.end());
    out << temp[0] << "\n";
  }
}

void zaparin::cmdCount(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon) > functor;
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

    functor = std::bind(isRight, _1, Vertexes, std::stoull(parameter));
  }

  out << std::count_if(plgs.begin(), plgs.end(), functor) << "\n";
}
//
//void zaparin::cmdMaxSeq(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out)
//{
//  Polygon plg;
//  std::vector< Point > temp;
//
//  using in_it = std::istream_iterator< Point >;
//  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(temp));
//
//  if (in.peek() != '\n')
//  {
//    throw InvalidCommand();
//  }
//  else
//  {
//    plg.points = temp;
//  }
//
//  MaxSeq maxSeq{ plg };
//  std::for_each(plgs.begin(), plgs.end(), std::ref(maxSeq));
//  out << std::fixed;
//  out.precision(1);
//  out << maxSeq.maxCounter << "\n";
//}
//
//void zaparin::cmdIntersections(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out)
//{
//  Polygon plg;
//  std::vector< Point > temp;
//
//  using in_it = std::istream_iterator< Point >;
//  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(temp));
//
//  if (in.peek() != '\n')
//  {
//    throw InvalidCommand();
//  }
//  else
//  {
//    plg.points = temp;
//  }
//
//  IsIntersected PlgIntersected{ plg };
//  std::for_each(plgs.begin(), plgs.end(), std::ref(PlgIntersected));
//
//  out << PlgIntersected.intersectionsCount << "\n";
//}
//
//bool zaparin::isNumeric(const std::string& str)
//{
//  char arr[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
//  for (int i = 0; i < 10; i++)
//  {
//    if (str[0] == arr[i])
//    {
//      return 1;
//    }
//  }
//  return 0;
//}

