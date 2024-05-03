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

double accumulateAreaMax(double areaMax, const kuzmina::Polygon& polygon)
{
  areaMax = std::max(areaMax, polygon.getArea());

  return areaMax;
}

size_t accumulateVertexesMax(size_t vertexesMax, const kuzmina::Polygon& polygon)
{
  vertexesMax = std::max(vertexesMax, polygon.points.size());

  return vertexesMax;
}

void kuzmina::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  if (polygons.size() < 1)
  {
    out << "<INVALID COMMAND>";
    return;
  }

  if (command == "AREA")
  {
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateAreaMax);
  }
  else if (command == "VERTEXES")
  {
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, accumulateVertexesMax);
  }
  else
  {
    out << "<INVALID COMMAND>";
    return;
  }
}

double accumulateAreaMin(double areaMin, const kuzmina::Polygon& polygon)
{
  areaMin = std::min(areaMin, polygon.getArea());

  return areaMin;
}

size_t accumulateVertexesMin(size_t vertexesMin, const kuzmina::Polygon& polygon)
{
  vertexesMin = std::min(vertexesMin, polygon.points.size());

  return vertexesMin;
}

void kuzmina::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  if (polygons.size() < 1)
  {
    out << "<INVALID COMMAND>";
    return;
  }

  if (command == "AREA")
  {
    double areaMax = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateAreaMax);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), areaMax, accumulateAreaMin);
  }
  else if (command == "VERTEXES")
  {
    size_t vertexesMax = std::accumulate(polygons.cbegin(), polygons.cend(), 0, accumulateVertexesMax);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), vertexesMax, accumulateVertexesMin);
  }
  else
  {
    out << "<INVALID COMMAND>";
    return;
  }
}

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
