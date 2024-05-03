#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <iomanip>
#include <limits>

using namespace std::placeholders;

double erfurt::AccumulateAreaParity::operator()(double area, const Polygon & poly, bool isEven)
{
  if (isEven == (poly.points.size() % 2 == 1))
  {
    area += poly.getArea();
  }
  return area;
}

void erfurt::accAreaParityEven(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto accArea = std::bind(AccumulateAreaParity{}, _1, _2, false);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
}

void erfurt::accAreaParityOdd(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto accArea = std::bind(AccumulateAreaParity{}, _1, _2, true);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
}

double erfurt::AccumulateAreaMean::operator()(double area, const Polygon & poly)
{
  area += poly.getArea() / count;
  return area;
}

void erfurt::accAreaMean(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto accArea = std::bind(AccumulateAreaMean{polygons.size()}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
}

double erfurt::AccumulateAreaNumOfVertex::operator()(double area, const Polygon & poly)
{
  if (poly.points.size() == numOfVertex)
  {
    area += poly.getArea();
  }
  return area;
}

void erfurt::accAreaNumOfVertex(const std::vector<Polygon> & polygons, std::ostream & out, std::size_t numOfVertex)
{
  auto accArea = std::bind(AccumulateAreaNumOfVertex{numOfVertex}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
}

void erfurt::area(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string temp;
  in >> temp;
  if (temp == "EVEN")
  {
    accAreaParityEven(polygons, out);
  }
  else if (temp == "ODD")
  {
    accAreaParityOdd(polygons, out);
  }
  else if (temp == "MEAN" && !polygons.empty())
  {
    accAreaMean(polygons, out);
  }
  else
  {
    try
    {
      int n = std::stoi(temp);
      if (n < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      accAreaNumOfVertex(polygons, out, n);
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
}

double erfurt::AccumulateMaxArea::operator()(double area, const Polygon & poly)
{
  area = std::max(area, poly.getArea());
  return area;
}

void erfurt::accMaxArea(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto maxArea = std::bind(AccumulateMaxArea{}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, maxArea);
}

std::size_t erfurt::AccumulateMaxVertexes::operator()(std::size_t vertexes, const Polygon & poly)
{
  vertexes = std::max(vertexes, poly.points.size());
  return vertexes;
}

void erfurt::accMaxVertexes(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto maxVertexes = std::bind(AccumulateMaxVertexes{}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, maxVertexes);
}

void erfurt::max(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string temp;
  in >> temp;
  if (temp == "AREA" && !polygons.empty())
  {
    accMaxArea(polygons, out);
  }
  else if (temp == "VERTEXES" && !polygons.empty())
  {
    accMaxVertexes(polygons, out);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

double erfurt::AccumulateMinArea::operator()(double area, const Polygon & poly)
{
  area = std::min(area, poly.getArea());
  return area;
}

void erfurt::accMinArea(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto minArea = std::bind(AccumulateMinArea{}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), std::numeric_limits<double>::max(), minArea);
}

std::size_t erfurt::AccumulateMinVertexes::operator()(std::size_t vertexes, const Polygon & poly)
{
  vertexes = std::min(vertexes, poly.points.size());
  return vertexes;
}

void erfurt::accMinVertexes(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto minVertexes = std::bind(AccumulateMinVertexes{}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), std::numeric_limits<size_t>::max(), minVertexes);
}

void erfurt::min(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string temp;
  in >> temp;
  if (temp == "AREA" && !polygons.empty())
  {
    accMinArea(polygons, out);
  }
  else if (temp == "VERTEXES" && !polygons.empty())
  {
    accMinVertexes(polygons, out);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

std::size_t erfurt::AccumulateCountParity::operator()(std::size_t count, const Polygon & poly, bool isEven)
{
  if (isEven == (poly.points.size() % 2 == 1))
  {
    count += 1;
  }
  return count;
}

void erfurt::accCountParityEven(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto accCount = std::bind(AccumulateCountParity{}, _1, _2, false);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, accCount);
}

void erfurt::accCountParityOdd(const std::vector<Polygon> & polygons, std::ostream & out)
{
  auto accCount = std::bind(AccumulateCountParity{}, _1, _2, true);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, accCount);
}

std::size_t erfurt::AccumulateCountNumOfVertex::operator()(std::size_t count, const Polygon & poly)
{
  if (poly.points.size() == numOfVertex)
  {
    count += 1;
  }
  return count;
}

void erfurt::accCountNumOfVertex(const std::vector<Polygon> & polygons, std::ostream & out, std::size_t numOfVertex)
{
  auto accCount = std::bind(AccumulateCountNumOfVertex{numOfVertex}, _1, _2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, accCount);
}

void erfurt::count(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  std::string temp;
  in >> temp;
  if (temp == "EVEN")
  {
    accCountParityEven(polygons, out);
  }
  else if (temp == "ODD")
  {
    accCountParityOdd(polygons, out);
  }
  else
  {
    try
    {
      size_t n = std::stoi(temp);
      if (n < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      accCountNumOfVertex(polygons, out, n);
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
}

bool erfurt::isPerm(const Polygon & poly1, const Polygon & poly2)
{
  if (poly1.points.size() != poly2.points.size())
  {
    return false;
  }
  auto perm = std::bind(isPointConsist, _1, poly2);
  return std::distance(poly2.points.cbegin(), poly2.points.cend()) == std::count_if(poly1.points.cbegin(), poly1.points.cend(), perm);
}

void erfurt::perm(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  Polygon poly;
  in >> poly;
  if (!in || poly.points.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  auto perm = std::bind(isPerm, _1, poly);
  out << count_if(polygons.cbegin(), polygons.cend(), perm);
}

bool erfurt::IdenticalPoly::operator()(const Polygon & poly1, const Polygon & poly2)
{
  return (poly1 == poly2) && (poly == poly1);
}

void erfurt::rmecho(std::vector<Polygon> & polygons, std::istream & in, std::ostream & out)
{
  Polygon poly;
  in >> poly;
  if (!in || poly.points.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  auto identical = std::bind(IdenticalPoly{ poly }, _1, _2);
  auto last = std::unique(polygons.begin(), polygons.end(), identical);
  std::size_t erased = std::distance(last, polygons.end());
  polygons.erase(last, polygons.end());
  out << erased;
}
