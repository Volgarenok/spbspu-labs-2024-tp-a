#include "commands.hpp"

#include <string>
#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>

void belokurskaya::cmd::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< double(const Polygon&) > resultFuncForArea;
  if (option == "EVEN")
  {
    resultFuncForArea = [](const Polygon& polygon) -> double
    {
      return polygon.points.size() % 2 != 0 ? cmd::subcmd::getPolygonArea(polygon) : 0.0;
    };
  }
  else if (option == "ODD")
  {
    resultFuncForArea = [](const Polygon& polygon) -> double
    {
      return polygon.points.size() % 2 == 0 ? cmd::subcmd::getPolygonArea(polygon) : 0.0;
    };
  }
  else if (option == "MEAN")
  {
    std::cout << "OUTPUT: AREA MEAN";
  }
  else
  {
    size_t numVertexes;
    try
    {
      numVertexes = std::stoull(option);

      if (numVertexes < 3)
      {
        throw std::invalid_argument("");
      }

      std::cout << "OUTPUT: AREA <num-of-vertexes>";
    }
    catch (const std::invalid_argument&)
    {
      std::cout << "INVALID COMMAND";
    }
  }
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
    [&resultFuncForArea](double sum, const Polygon& polygon)
    {
      return sum + resultFuncForArea(polygon);
    });
}

void belokurskaya::cmd::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  if (option == "AREA")
  {
    std::cout << "OUTPUT: MIN AREA";
  }
  else if (option == "VERTEXES")
  {
    std::cout << "OUTPUT: MIN VERTEXES";
  }
  else
  {
    std::cout << "INVALID COMMAND";
  }
}

void belokurskaya::cmd::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  if (option == "AREA")
  {
    std::cout << "OUTPUT: MAX AREA";
  }
  else if (option == "VERTEXES")
  {
    std::cout << "OUTPUT: MAX VERTEXES";
  }
  else
  {
    std::cout << "INVALID COMMAND";
  }
}

void belokurskaya::cmd::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  if (option == "EVEN")
  {
    std::cout << "OUTPUT: COUNT EVEN";
  }
  else if (option == "ODD")
  {
    std::cout << "OUTPUT: COUNT ODD";
  }
  else if (option == "MEAN")
  {
    std::cout << "OUTPUT: COUNT MEAN";
  }
  else
  {
    size_t numVertexes;
    try
    {
      numVertexes = std::stoull(option);

      if (numVertexes < 3)
      {
        throw std::invalid_argument("");
      }

      std::cout << "OUTPUT: COUNT <num-of-vertexes>";
    }
    catch (const std::invalid_argument&)
    {
      std::cout << "INVALID COMMAND";
    }
  }
}

double belokurskaya::cmd::subcmd::getTriangleArea(const Point& p1, const Point& p2, const Point& p3)
{
  return 0.5 * std::abs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y));
}

double belokurskaya::cmd::subcmd::getPolygonArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }
  std::vector< double > triangleAreas(polygon.points.size() - 2);
  using namespace std::placeholders;
  std::transform
  (
    polygon.points.begin() + 2,
    polygon.points.end(),
    std::next(polygon.points.begin(), 1),
    triangleAreas.begin(),
    std::bind(&cmd::subcmd::getTriangleArea, polygon.points[0], _1, _2)
  );
  return std::accumulate(triangleAreas.begin(), triangleAreas.end(), 0.0);
}

double belokurskaya::cmd::subcmd::getPolygonAreaEvenOrOdd(const Polygon& polygon, const bool isEven)
{
  double sumAreas = 0.0;
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    sumAreas = cmd::subcmd::getPolygonArea(polygon);
  }
  return sumAreas;
}

size_t belokurskaya::cmd::subcmd::getCountVertexes(const Polygon& polygon)
{
  return polygon.points.size();
}