#include "Commands.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <cctype>
#include <string>
#include <numeric>
#include <iomanip>
#include <algorithm>

bool isOdd(const kuzmina::Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

bool isEven(const kuzmina::Polygon& polygon)
{
  return !isOdd(polygon);
}

bool hasNVertexes(const kuzmina::Polygon& polygon, const size_t numberOfVertexes)
{
  return polygon.points.size() == numberOfVertexes;
}

double countAreaMean(double area, const kuzmina::Polygon& polygon, const size_t numberOfPolygons)
{
  area += getArea(polygon) / numberOfPolygons;

  return area;
}

void kuzmina::doArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::map< std::string, std::function< bool(const Polygon&) > > subCommands;
  subCommands["ODD"] = isOdd;
  subCommands["EVEN"] = isEven;

  std::string command = "";
  in >> command;

  std::vector< Polygon > toProcess;
  std::function< double(const Polygon&) > areaCounter = getArea;

  try
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(toProcess), subCommands.at(command));
  }
  catch (const std::out_of_range&)
  {
    if (command == "MEAN")
    {
      if (polygons.size() < 1)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }

      using namespace std::placeholders;
      toProcess = polygons;
      areaCounter = std::bind(countAreaMean, 0.0, _1, polygons.size());
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

      using namespace std::placeholders;
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(toProcess), std::bind(hasNVertexes, _1, numberOfPoints));
    }
  }

  std::vector< double > areaToProcess;
  std::transform(toProcess.cbegin(), toProcess.cend(), std::back_inserter(areaToProcess), areaCounter);

  out << std::fixed << std::setprecision(1) << std::accumulate(areaToProcess.cbegin(), areaToProcess.cend(), 0.0);
}

void kuzmina::doMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  if (polygons.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (command == "AREA")
  {
    std::vector< double > areaToProcess;
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areaToProcess), getArea);

    out << std::fixed << std::setprecision(1) << *std::max_element(areaToProcess.cbegin(), areaToProcess.cend());
  }
  else if (command == "VERTEXES")
  {
    out << std::max_element(polygons.cbegin(), polygons.cend(), comparePolygonPointsSize)->points.size();
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kuzmina::doMin(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  if (polygons.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (command == "AREA")
  {
    std::vector< double > areaToProcess;
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areaToProcess), getArea);

    out << std::fixed << std::setprecision(1) << *std::min_element(areaToProcess.cbegin(), areaToProcess.cend());
  }
  else if (command == "VERTEXES")
  {
    out << std::min_element(polygons.cbegin(), polygons.cend(), comparePolygonPointsSize)->points.size();
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kuzmina::doCount(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string command = "";
  in >> command;

  if (command == "ODD")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }
  else if (command == "EVEN")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isEven);
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

    using namespace std::placeholders;
    out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(hasNVertexes, _1, numberOfPoints));
  }
}

bool isRight(const kuzmina::Polygon& polygon)
{
  return polygon.hasRightAngle();
}

void kuzmina::doRightShapes(std::ostream& out, const std::vector< Polygon >& polygons)
{
  out << std::count_if(polygons.cbegin(), polygons.cend(), isRight);
}

bool hasSamePoints(const kuzmina::Point& delta, const kuzmina::Point& point, const kuzmina::Polygon& polygon)
{
  kuzmina::Point dest = { point.x + delta.x, point.y + delta.y };

  using namespace std::placeholders;
  auto accSamePoints = std::bind(kuzmina::comparePoints, dest, _1);
  return std::find_if(polygon.points.cbegin(), polygon.points.cend(), accSamePoints) != polygon.points.cend();
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

  int numberOfPoints = std::distance(polygon1.points.cbegin(), polygon1.points.cend());
  return std::count_if(polygon1.points.cbegin(), polygon1.points.cend(), accSamePoints) == numberOfPoints;
}

void kuzmina::doSame(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  Polygon polygonToCompare;
  in >> polygonToCompare;

  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  using namespace std::placeholders;
  std::function< bool(const Polygon&) > accSame = std::bind(areSame, _1, polygonToCompare);

  out << count_if(polygons.cbegin(), polygons.cend(), accSame);
}
