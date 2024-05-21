#include "Commands.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <cctype>
#include <string>
#include <numeric>
#include <iomanip>
#include <algorithm>

double accumulateAreaOddOrEven(double area, const kuzmina::Polygon& polygon, std::function< bool(const kuzmina::Polygon&) > condition)
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

double accumulateAreaNumberOfVertexes(double area, const kuzmina::Polygon& polygon, size_t numberOfVertexes)
{
  if (polygon.points.size() == numberOfVertexes)
  {
    area += polygon.getArea();
  }

  return area;
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
      throw std::logic_error("<INVALID COMMAND>");
    }

    accArea = std::bind(accumulateAreaMean, _1, _2, polygons.size());
  }
  else
  {
    size_t numberOfPoints = 0;

    try
    {
      numberOfPoints = std::stoull(command);
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    if (numberOfPoints < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    accArea = std::bind(accumulateAreaNumberOfVertexes, _1, _2, numberOfPoints);
  }

  out << std::fixed << std::setprecision(1) << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
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
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (command == "AREA")
  {
    out << std::fixed << std::setprecision(1) << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateAreaMax);
  }
  else if (command == "VERTEXES")
  {
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, accumulateVertexesMax);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
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
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (command == "AREA")
  {
    double areaMax = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateAreaMax);
    out << std::fixed << std::setprecision(1) << std::accumulate(polygons.cbegin(), polygons.cend(), areaMax, accumulateAreaMin);
  }
  else if (command == "VERTEXES")
  {
    size_t vertexesMax = std::accumulate(polygons.cbegin(), polygons.cend(), 0, accumulateVertexesMax);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), vertexesMax, accumulateVertexesMin);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

int accumulateCountOddOrEven(int count, const kuzmina::Polygon& polygon, std::function< bool(const kuzmina::Polygon&) > condition)
{
  if (condition(polygon))
  {
    ++count;
  }

  return count;
}

int accumulateCountNumberOfVertexes(int count, const kuzmina::Polygon& polygon, size_t numberOfVertexes)
{
  if (polygon.points.size() == numberOfVertexes)
  {
    ++count;
  }

  return count;
}

void kuzmina::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  using namespace std::placeholders;

  std::function< int(int, const Polygon&) > accCount;
  if (command == "ODD")
  {
    accCount = std::bind(accumulateCountOddOrEven, _1, _2, isOdd);
  }
  else if (command == "EVEN")
  {
    accCount = std::bind(accumulateCountOddOrEven, _1, _2, isEven);
  }
  else
  {
    size_t numberOfPoints = 0;

    try
    {
      numberOfPoints = std::stoull(command);
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    if (numberOfPoints < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    accCount = std::bind(accumulateCountNumberOfVertexes, _1, _2, numberOfPoints);
  }

  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, accCount);
}

bool isRight(const kuzmina::Polygon& polygon)
{
  return polygon.countRightAngles();
}

void kuzmina::rightShapes(std::ostream& out, const std::vector< Polygon >& polygons)
{
  out << std::count_if(polygons.cbegin(), polygons.cend(), isRight);
}

bool hasSamePoints(const kuzmina::Point& delta, const kuzmina::Point& point, const kuzmina::Polygon& polygon)
{
  kuzmina::Point dest = { point.x + delta.x, point.y + delta.y };

  return std::find(polygon.points.cbegin(), polygon.points.cend(), dest) != polygon.points.cend();
}

bool areSame(const kuzmina::Polygon& polygon1, const kuzmina::Polygon& polygon2)
{
  if (polygon1.points.size() != polygon2.points.size())
  {
    return false;
  }

  int dx = polygon2.points[0].x - polygon1.points[0].x;
  int dy = polygon2.points[0].y - polygon1.points[0].y;
  kuzmina::Point delta = { dx, dy };

  using namespace std::placeholders;
  std::function< bool(const kuzmina::Point&) > accSamePoints = std::bind(hasSamePoints, delta, _1, polygon2);

  return std::count_if(polygon1.points.cbegin(), polygon1.points.cend(), accSamePoints) ==
         std::distance(polygon1.points.cbegin(), polygon1.points.cend());
}

void kuzmina::same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  Polygon polygonToCompare;
  in >> polygonToCompare;

  if (!in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  using namespace std::placeholders;
  std::function< bool(const Polygon&) > accSame = std::bind(areSame, _1, polygonToCompare);

  out << count_if(polygons.cbegin(), polygons.cend(), accSame);
}
