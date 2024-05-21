#include "polygon.hpp"

std::istream& chernikova::operator>>(std::istream& in, chernikova::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> chernikova::DelimiterI{'(' };
  in >> dest.x;
  in >> chernikova::DelimiterI{';' };
  in >> dest.y;
  in >> chernikova::DelimiterI{')' };
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, chernikova::Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  using iter = std::istream_iterator< chernikova::Point >;
  dest.points.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points));
  if (dest.points.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

bool chernikova::isEven(const chernikova::Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool chernikova::isOdd(const chernikova::Polygon& polygon)
{
  return !isEven(polygon);
}

double chernikova::calcArea(const chernikova::Point& left, const chernikova::Point& right)
{
  return 0.5 * (left.x * right.y - right.x * left.y);
}

double chernikova::getArea(const chernikova::Polygon& polygon)
{
  double res = 0.0;
  for (size_t i = 0; i < polygon.points.size() - 1; ++i)
  {
    res += chernikova::calcArea(polygon.points[i], polygon.points[i + 1]);
  }
  res += chernikova::calcArea(polygon.points.back(), polygon.points.front());
  return std::abs(res);
}

double chernikova::sumArea(double cur, const chernikova::Polygon& polygon)
{
  return cur + chernikova::getArea(polygon);
}

bool chernikova::isNecessaryVertex(const chernikova::Polygon& polygon, size_t count)
{
  return polygon.points.size() == count;
}

double chernikova::chooseGreaterArea(double cur, const Polygon& polygon)
{
  double area = chernikova::getArea(polygon);
  return (cur > area) ? cur : area;
}

size_t chernikova::chooseGreaterVertexes(double cur, const Polygon& polygon)
{
  size_t count = polygon.points.size();
  return (cur > count) ? cur : count;
}

double chernikova::chooseLessArea(double cur, const chernikova::Polygon& polygon)
{
  double area = chernikova::getArea(polygon);
  return (cur < area) ? cur : area;
}

size_t chernikova::chooseLessVertexes(double cur, const chernikova::Polygon& polygon)
{
  size_t count = polygon.points.size();
  return (cur < count) ? cur : count;
}

void chernikova::getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< Polygon > even_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), chernikova::isEven);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, chernikova::sumArea) << "\n";
}

void chernikova::getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< Polygon > odd_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), chernikova::isOdd);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(odd_polygons.begin(), odd_polygons.end(), 0.0, chernikova::sumArea) << "\n";
}

void chernikova::getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  size_t count = polygons.size();
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, chernikova::sumArea) / count << "\n";
}

void chernikova::getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  if (count < 3)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::vector< Polygon > vertexes_polygons;
  using namespace std::placeholders;
  auto pred = std::bind(chernikova::isNecessaryVertex, _1, count);
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vertexes_polygons), pred);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(vertexes_polygons.begin(), vertexes_polygons.end(), 0.0, sumArea) << "\n";
}

void chernikova::getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, chernikova::chooseGreaterArea) << "\n";
}

void chernikova::getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  StreamGuard streamGuard(out);
  out << std::accumulate(polygons.begin(), polygons.end(), 0, chernikova::chooseGreaterVertexes) << "\n";
}

void chernikova::getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(polygons.begin(), polygons.end(), chernikova::getArea(polygons.front()), chernikova::chooseLessArea) << "\n";
}

void chernikova::getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  StreamGuard streamGuard(out);
  out << std::accumulate(polygons.begin(), polygons.end(), polygons.front().points.size(), chernikova::chooseLessVertexes) << "\n";
}

void chernikova::getCountEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::count_if(polygons.begin(), polygons.end(), chernikova::isEven) << "\n";
}

void chernikova::getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::count_if(polygons.begin(), polygons.end(), chernikova::isOdd) << "\n";
}

void chernikova::getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  if (count < 3)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  auto pred = std::bind(chernikova::isNecessaryVertex, _1, count);
  StreamGuard streamGuard(out);
  out << count_if(polygons.begin(), polygons.end(), pred) << "\n";
}

bool chernikova::isEqualPolygon(const Polygon& lhs, const Polygon& rhs)
{
  return (rhs.points == lhs.points);
}

chernikova::Polygon chernikova::duplicator(std::vector< Polygon >& polygons, const Polygon& polygon, const Polygon& desiredPolygon)
{
  if (isEqualPolygon(polygon, desiredPolygon))
  {
    polygons.push_back(polygon);
  }
  return polygon;
}

void chernikova::echo(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
{
  using namespace std::placeholders;
  auto equal = std::bind(chernikova::isEqualPolygon, _1, polygon);
  size_t count = std::count_if(polygons.cbegin(), polygons.cend(), equal);
  auto binary_op = std::bind(chernikova::duplicator, polygons, _1, polygon);
  std::transform(std::make_move_iterator(polygons.begin()), std::make_move_iterator(polygons.end()),
                 std::back_inserter(polygons), binary_op);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << count << "\n";
}

bool chernikova::hasIntersection(const Polygon& lhs, const Polygon& rhs)
{
  Point minLhs = *std::min_element(lhs.points.begin(), lhs.points.end());
  Point minRhs = *std::min_element(rhs.points.begin(), rhs.points.end());
  Point maxLhs = *std::max_element(lhs.points.begin(), lhs.points.end());
  Point maxRhs = *std::max_element(rhs.points.begin(), rhs.points.end());

  return (minLhs <= maxRhs) && (maxLhs >= minRhs) || (minRhs <= maxLhs) && (maxRhs >= minLhs);
}

void chernikova::intersections(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  auto pred = std::bind(hasIntersection, _1, polygon);
  out << std::count_if(polygons.begin(), polygons.end(), pred) << "\n";
}

bool chernikova::checkRightAngle(const Polygon& polygon, size_t i)
{
  const Point& p1 = polygon.points[i];
  const Point& p2 = polygon.points[(i + 1) % polygon.points.size()];
  const Point& p3 = polygon.points[(i + 2) % polygon.points.size()];

  double dotProduct = (p2.x - p1.x) * (p3.x - p2.x) + (p2.y - p1.y) * (p3.y - p2.y);
  return dotProduct == 0;
}

bool chernikova::hasRightAngle(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return false;
  }

  auto it = std::find_if(polygon.points.begin(), polygon.points.end(), [&](const Point& p)
  {
    size_t i = &p - &polygon.points[0];
    return checkRightAngle(polygon, i);
  });

  return it != polygon.points.end();
}

void chernikova::rightShapes(const std::vector< Polygon >& polygons, std::ostream& out)
{

}

