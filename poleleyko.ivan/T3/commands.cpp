#include "commands.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "scopeGuard.hpp"
#include "polygon.hpp"

namespace poleleyko
{
  class AreaCounter
  {
    public:
      explicit AreaCounter(const Point &);
      double operator()(double currArea, const Point & b, const Point & c);
    private:
      Point a_;
  };
  double getArea(const Polygon & polygon);
  double countMeanArea(double currArea, const Polygon & polygon, size_t count);
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  bool isNumOfVertexes(const Polygon & polygon, size_t numOfVertexes);

  bool areaComparator(const Polygon & lhs, const Polygon & rhs);
  void maxArea(const std::vector< Polygon > & shapes, std::ostream & out);
  void minArea(const std::vector< Polygon > & shapes, std::ostream & out);

  bool vertexesComparator(const Polygon & lhs, const Polygon & rhs);
  void maxVertexes(const std::vector< Polygon > & shapes, std::ostream & out);
  void minVertexes(const std::vector< Polygon > & shapes, std::ostream & out);

  bool isEvenVertexesCount(const Polygon & polygon);
  bool isOddVertexesCount(const Polygon & polygon);

  bool isEqualLines(const Point & a1, const Point & a2, const Point & b1, const Point & b2);
  bool isSquareTriangle(const Point & a, const Point & b, const Point & c);
  bool isRectangle(const Polygon & polygon);

  bool xComparator(const Point & lhs, const Point & rhs);
  bool yComparator(const Point & lhs, const Point & rhs);
  using rect_t = std::pair< Point, Point >;
  rect_t extendFrameRect(rect_t frameRect, const Polygon & polygon);
  bool isPointInRect(const Point & point, const rect_t & rect);
}

void poleleyko::area(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  ScopeGuard guard(out);
  std::map< std::string, std::function< bool(const Polygon &) > > predicates;
  predicates["EVEN"] = isEven;
  predicates["ODD"] = isOdd;
  std::string cmd;
  in >> cmd;
  std::function< bool(const Polygon &) > predicate;
  std::vector< Polygon > filteredShapes;
  std::function< double(const Polygon &) > areaFunctor = getArea;
  try
  {
    predicate = predicates.at(cmd);
    std::copy_if(shapes.cbegin(), shapes.cend(), std::back_inserter(filteredShapes), predicate);
  }
  catch (const std::out_of_range &)
  {
    if (cmd == "MEAN")
    {
      if (shapes.empty())
      {
        throw std::logic_error("There are no shapes");
      }
      using namespace std::placeholders;
      areaFunctor = std::bind(countMeanArea, 0.0, _1, shapes.size());
      filteredShapes = shapes;
    }
    else
    {
      using namespace std::placeholders;
      size_t numOfVertexes = std::stoull(cmd);
      if (numOfVertexes < 3)
      {
        throw std::logic_error("Invalid vertexes count");
      }
      predicate = std::bind(isNumOfVertexes, _1, numOfVertexes);
      std::copy_if(shapes.cbegin(), shapes.cend(), std::back_inserter(filteredShapes), predicate);
    }
  }
  std::vector< double > areas;
  std::transform(filteredShapes.cbegin(), filteredShapes.cend(), std::back_inserter(areas), areaFunctor);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

void poleleyko::max(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  if (shapes.empty())
  {
    throw std::logic_error("There are no shapes");
  }
  ScopeGuard guard(out);
  std::map< std::string, std::function< void() > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(maxArea, std::cref(shapes), std::ref(out));
    cmds["VERTEXES"] = std::bind(maxVertexes, std::cref(shapes), std::ref(out));
  }
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1);
  cmds.at(cmd)();
}

void poleleyko::min(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  if (shapes.empty())
  {
    throw std::logic_error("There are no shapes");
  }
  ScopeGuard guard(out);
  std::map< std::string, std::function< void() > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(minArea, std::ref(shapes), std::ref(out));
    cmds["VERTEXES"] = std::bind(minVertexes, std::ref(shapes), std::ref(out));
  }
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1);
  cmds.at(cmd)();
}

void poleleyko::count(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  std::map< std::string, std::function< bool(const Polygon &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(isEvenVertexesCount, _1);
    cmds["ODD"] = std::bind(isOddVertexesCount, _1);
  }
  std::function< double(const Polygon &) > countFunctor;
  std::string cmd;
  in >> cmd;
  try
  {
    countFunctor = cmds.at(cmd);
  }
  catch (const std::out_of_range &)
  {
    size_t numOfVertexes = std::stoull(cmd);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("Invalid vertexes count");
    }
    using namespace std::placeholders;
    countFunctor = std::bind(isNumOfVertexes, _1, numOfVertexes);
  }
  out << std::count_if(shapes.cbegin(), shapes.cend(), countFunctor);
}

void poleleyko::rect(const std::vector< Polygon > & shapes, std::istream &, std::ostream & out)
{
  out << std::count_if(shapes.cbegin(), shapes.cend(), isRectangle);
}

void poleleyko::inFrame(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("Invalid polygon to compare");
  }
  auto frameRect = std::accumulate(shapes.cbegin(), shapes.cend(), rect_t { { 0, 0 }, { 0, 0 } }, extendFrameRect);
  using namespace std::placeholders;
  auto isInFrameRect = std::bind(isPointInRect, _1, std::ref(frameRect));
  size_t count = std::count_if(polygon.points.cbegin(), polygon.points.cend(), isInFrameRect);
  if (count == polygon.points.size())
  {
    out << "<TRUE>";
  }
  else
  {
    out << "<FALSE>";
  }
}

void poleleyko::lessArea(const std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("Invalid polygon to compare");
  }
  using namespace std::placeholders;
  auto predicate = std::bind(areaComparator, _1, std::ref(polygon));
  size_t result = std::count_if(shapes.cbegin(), shapes.cend(), predicate);
  out << result;
}

poleleyko::AreaCounter::AreaCounter(const Point & a):
  a_(a)
{}

double poleleyko::AreaCounter::operator()(double currArea, const Point & b, const Point & c)
{
  currArea += 0.5 * std::abs((b.x - a_.x) * (c.y - a_.y) - (c.x - a_.x) * (b.y - a_.y));
  a_ = b;
  return currArea;
}

double poleleyko::getArea(const Polygon & polygon)
{
  const std::vector< Point > & points = polygon.points;
  if (points.size() < 3)
  {
    return 0.0;
  }
  using namespace std::placeholders;
  auto areaFunctor = std::bind(AreaCounter(points.at(1)), 0.0, _1, points.at(0));
  std::vector< double > areas;
  std::transform(points.cbegin(), points.cend(), std::back_inserter(areas), areaFunctor);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

double poleleyko::countMeanArea(double currArea, const Polygon & polygon, size_t count)
{
  return currArea + getArea(polygon) / count;
}

bool poleleyko::isEven(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool poleleyko::isOdd(const Polygon & polygon)
{
  return !isEven(polygon);
}

bool poleleyko::isNumOfVertexes(const Polygon & polygon, size_t numOfVertexes)
{
  return numOfVertexes == polygon.points.size();
}

bool poleleyko::areaComparator(const Polygon & lhs, const Polygon & rhs)
{
  return getArea(lhs) < getArea(rhs);
}

void poleleyko::maxArea(const std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::max_element(shapes.cbegin(), shapes.cend(), areaComparator);
  out << getArea(*result);
}

void poleleyko::minArea(const std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::min_element(shapes.cbegin(), shapes.cend(), areaComparator);
  out << getArea(*result);
}

bool poleleyko::vertexesComparator(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void poleleyko::maxVertexes(const std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::max_element(shapes.cbegin(), shapes.cend(), vertexesComparator);
  out << result->points.size();
}

void poleleyko::minVertexes(const std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::min_element(shapes.cbegin(), shapes.cend(), vertexesComparator);
  out << result->points.size();
}

bool poleleyko::isEvenVertexesCount(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool poleleyko::isOddVertexesCount(const Polygon & polygon)
{
  return !isEvenVertexesCount(polygon);
}

bool poleleyko::isSquareTriangle(const Point & a, const Point & b, const Point & c)
{
  double ab = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  double ac = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y);
  double bc = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y);
  return ac == ab + bc || ab == ac + bc || bc == ac + ab;
}

bool poleleyko::isEqualLines(const Point & a1, const Point & a2, const Point & b1, const Point & b2)
{
  return std::abs(a1.x - a2.x) == std::abs(b1.x - b2.x) && std::abs(a1.y - a2.y) == std::abs(b1.y - b2.y);
}

bool poleleyko::isRectangle(const Polygon & polygon)
{
  const std::vector< Point > & points = polygon.points;
  if (points.size() != 4)
  {
    return false;
  }
  const Point & a = points.at(0);
  const Point & b = points.at(1);
  const Point & c = points.at(2);
  const Point & d = points.at(3);
  return isSquareTriangle(a, b, c) && (isEqualLines(a, b, c, d) || isEqualLines(a, c, b, d) || isEqualLines(a, d, b, c));
}

bool poleleyko::xComparator(const Point & lhs, const Point & rhs)
{
  return lhs.x < rhs.x;
}

bool poleleyko::yComparator(const Point & lhs, const Point & rhs)
{
  return lhs.y < rhs.y;
}

poleleyko::rect_t poleleyko::extendFrameRect(rect_t frameRect, const Polygon & polygon)
{
  int ax = std::min_element(polygon.points.cbegin(), polygon.points.cend(), xComparator)->x;
  int ay = std::min_element(polygon.points.cbegin(), polygon.points.cend(), yComparator)->y;

  int bx = std::max_element(polygon.points.cbegin(), polygon.points.cend(), xComparator)->x;
  int by = std::max_element(polygon.points.cbegin(), polygon.points.cend(), yComparator)->y;

  frameRect.first.x = std::min(ax, frameRect.first.x);
  frameRect.first.y = std::min(ay, frameRect.first.y);

  frameRect.second.x = std::max(bx, frameRect.second.x);
  frameRect.second.y = std::max(by, frameRect.second.y);

  return frameRect;
}

bool poleleyko::isPointInRect(const Point & point, const rect_t & rect)
{
  bool tmp1 = rect.first.x <= point.x && rect.second.x >= point.x;
  bool tmp2 = tmp1 && rect.first.y <= point.y;
  return tmp2 && rect.second.y >= point.y;
}