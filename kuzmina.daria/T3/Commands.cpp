#include "Commands.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <cctype>
#include <string>
#include <numeric>

double accumulateAreaOddOrEven(double area, const kuzmina::Polygon& polygon, std::function< bool (const kuzmina::Polygon&) > condition)
{
  if (condition(polygon))
  {
    area += polygon.getArea();
  }

  return area;
}

bool isOdd(const kuzmina::Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

bool isEven(const kuzmina::Polygon& polygon)
{
  return !isOdd(polygon);
}

double accumulateAreaMean(double area, const kuzmina::Polygon& polygon, int numberOfPolygons)
{
  area += polygon.getArea() / numberOfPolygons;

  return area;
}

double accumulateAreaNumberOfVertexes(double area, const kuzmina::Polygon& polygon, int numberOfVertexes)
{
  if (polygon.points.size() == numberOfVertexes)
  {
    area += polygon.getArea();
  }

  return area;
}

bool isNumber(std::string s)
{
  for (int i = 0; i < s.length(); ++i)
  {
    if (!std::isdigit(s[i]))
    {
      return false;
    }
  }

  return true;
}

void kuzmina::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  using namespace std::placeholders;

  std::function< double(double, const Polygon&) > accArea;
  if (command == "ODD")
  {
    accArea = std::bind(accumulateAreaOddOrEven, _1, _2, isOdd);
  }
  else if (command == "EVEN")
  {
    accArea = std::bind(accumulateAreaOddOrEven, _1, _2, isEven);
  }
  else if (command == "MEAN")
  {
    if (polygons.size() < 1)
    {
      out << "<INVALID COMMAND>";
      return;
    }

    accArea = std::bind(accumulateAreaMean, _1, _2, polygons.size());
  }
  else
  {
    if (!isNumber(command))
    {
      out << "<INVALID COMMAND>";
      return;
    }

    int numberOfPoints = std::stoi(command);
    if (numberOfPoints < 3)
      {
      out << "<INVALID COMMAND>";
      return;
    }

    accArea = std::bind(accumulateAreaNumberOfVertexes, _1, _2, numberOfPoints);
  }

  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
}

//void kuzmina::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
//{
//
//}
//
//void kuzmina::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
//{
//
//}
//
//void kuzmina::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
//{
//
//}
//
//void kuzmina::same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
//{
//
//}
//
//void kuzmina::rightshapes(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
//{
//
//}
