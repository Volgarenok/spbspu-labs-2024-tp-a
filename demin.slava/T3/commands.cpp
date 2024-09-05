#include "commands.hpp"

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "figures.hpp"

bool odd(const Polygon &p);
bool even(const Polygon &p);
bool checkVertexes(size_t count, const Polygon &p);
bool compareAreas(const Polygon &p1, const Polygon &p2);
bool compareVertexes(const Polygon &p1, const Polygon &p2);
bool countAngle(Point &p1, Point &p2, const Point &p3);
bool isRight(const Polygon &polygon);
double getArea(const Polygon &points);
std::pair< demin::Point, demin::Point > findFrame(const std::pair< Point, Point > &res, const Polygon &polygon);
bool compareX(const Point &p1, const Point &p2);
bool compareY(const Point &p1, const Point &p2);
bool isInFrame(std::pair< Point, Point > frame, const Point &point);

struct AccumulateArea
{
  Point p1;

  double operator()(double &res, const Point &p2, const demin::Point &p3)
  {
    res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
    p1 = p2;
    return res;
  }
}

bool odd(const Polygon &p)
{
  return p.points.size() % 2;
}

bool even(const Polygon &p)
{
  return !odd(p);
}

bool checkVertexes(size_t count, const Polygon &p)
{
  return p.points.size() == count;
}

bool compareAreas(const Polygon &p1, const Polygon &p2)
{
  return getArea(p1) < getArea(p2);
}

bool compareVertexes(const Polygon &p1, const Polygon &p2)
{
  return p1.points.size() < p2.points.size();
}

double getArea(const Polygon &points)
{
  using namespace std::placeholders;
  auto res = std::bind(AccumulateArea{points.points[1]}, _1, _2, points.points[0]);
  return std::accumulate(points.points.cbegin(), points.points.cend(), 0.0, res);
}

bool isRight(const demin::Polygon &polygon)
{
  using namespace std::placeholders;
  Point p1 = polygon.points[polygon.points.size() - 1];
  Point p2 = polygon.points[polygon.points.size() - 2];
  auto countAngleFilter = std::bind(countAngle, std::ref(p1), std::ref(p2), _1);

  return std::find_if(polygon.points.cbegin(), polygon.points.cend(), countAngleFilter) != polygon.points.cend();
}

bool countAngle(Point &p1, Point &p2, const Point &p3)
{
  Point side1 = {p2.x - p1.x, p2.y - p1.y};
  Point side2 = {p3.x - p1.x, p3.y - p1.y};

  p1 = p2;
  p2 = p3;

  return side1.x * side2.x + side1.y * side2.y == 0;
}

std::pair< demin::Point, demin::Point > findFrame(const std::pair< Point, Point > &res, const Polygon &polygon)
{
  auto xPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compareX);
  auto yPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compareY);

  std::pair< Point, Point > updatedRes = res;

  updatedRes.second.x = std::max(res.second.x, xPair.second->x);
  updatedRes.second.y = std::max(res.second.y, yPair.second->y);
  updatedRes.first.x = std::min(res.first.x, xPair.first->x);
  updatedRes.first.y = std::min(res.first.y, yPair.first->y);

  return updatedRes;
}

bool compareX(const Point &p1, const Point &p2)
{
  return p1.x < p2.x;
}

bool compareY(const Point &p1, const Point &p2)
{
  return p1.y < p2.y;
}

bool isInFrame(std::pair< Point, Point > frame, const Point &point)
{
  bool condition = frame.first.x <= point.x && frame.second.x >= point.x;
  condition = condition && frame.first.y <= point.y && frame.second.y >= point.y;
  return condition;
}

void demin::doarea(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcommand = "";
  std::cin >> subcommand;
  std::vector< Polygon > filteredPolygons;
  std::function< double(const Polygon &) > countArea = getArea;

  if (subcommand == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), even);
  }
  else if (subcommand == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), odd);
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("<INVALID COMMAD>");
    }

    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons));
  }
  else
  {
    size_t nVertexes = 0;
    try
    {
      nVertexes = std::stoull(subcommand);
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAD>");
    }

    if (nVertexes < 3)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAD>");
    }

    using namespace std::placeholders;
    auto vertexesFilter = std::bind(checkVertexes, nVertexes, _1);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), vertexesFilter);
  }

  std::vector< double > areas;
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), countArea);
  double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (subcommand == "MEAN")
  {
    result /= polygons.size();
  }
  out << result << '\n';
}

void demin::domin(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    in.setstate(std::ios::failbit);
    throw std::logic_error("<INVALID COMMAD>");
  }

  std::vector< Polygon >::const_iterator min;
  std::string subcommand;
  std::cin >> subcommand;

  if (subcommand == "AREA")
  {
    min = std::min_element(polygons.cbegin(), polygons.cend(), compareAreas);
    out << getArea(*min) << '\n';
  }
  else if (subcommand == "VERTEXES")
  {
    min = std::min_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    out << (*min).points.size() << '\n';
  }
  else
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("INVALID COMMAD>");
  }
}

void demin::domax(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    in.setstate(std::ios::failbit);
    throw std::logic_error("<INVALID COMMAD>");
  }

  std::vector< Polygon >::const_iterator max;
  std::string subcommand;
  std::cin >> subcommand;

  if (subcommand == "AREA")
  {
    max = std::max_element(polygons.cbegin(), polygons.cend(), compareAreas);
    out << getArea(*max) << '\n';
  }
  else if (subcommand == "VERTEXES")
  {
    max = std::max_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    out << (*max).points.size() << '\n';
  }
  else
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("<INVALID COMMAD>>");
  }
}

void demin::count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  int res = 0.0;
  std::string subcommand = "";
  std::cin >> subcommand;

  if (subcommand == "EVEN")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), even);
  }
  else if (subcommand == "ODD")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), odd);
  }
  else
  {
    size_t nVertexes = 0;
    try
    {
      nVertexes = std::stoull(subcommand);
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    if (nVertexes < 3)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    using namespace std::placeholders;
    auto counter = std::bind(checkVertexes, nVertexes, _1);
    res = std::count_if(polygons.cbegin(), polygons.cend(), counter);
  }

  out << res << '\n';
}

void demin::lessArea(const std::vector< Polygon > &shapes, std::istream &in, std::ostream &out)
{
  Polygon polygon;
  in >> polygon;
  if (polygon.points.empty() || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  out << std::count_if(shapes.cbegin(), shapes.cend(), std::bind(compareAreas, _1, polygon)) << '\n';
}

void demin::doRightShapes(const std::vector< Polygon > &polygons, std::ostream &out)
{
  out << std::count_if(polygons.cbegin(), polygons.cend(), isRight) << '\n';
}

void demin::doInFrame(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon polygon;
  in >> polygon;

  if (polygon.points.empty() || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::pair< Point, Point > initFrame = {
    {0, 0},
    {0, 0}
  };
  std::pair< Point, Point > frame = std::accumulate(polygons.cbegin(), polygons.cend(), initFrame, findFrame);

  auto predicate = std::bind(isInFrame, frame, std::placeholders::_1);
  size_t howManyInFrame = std::count_if(polygon.points.cbegin(), polygon.points.cend(), predicate);

  out << (howManyInFrame == polygon.points.size() ? "<TRUE>" : "<FALSE>") << '\n';
}
