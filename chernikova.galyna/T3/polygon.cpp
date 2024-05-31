#include "polygon.hpp"
#include <string>
#include <interface.hpp>

std::istream& chernikova::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char symbol = 0;
  in >> ExactSymbolSavedI{ ' ', symbol };
  in >> ExactSymbolSavedI{ '(', symbol };
  in >> dest.x;
  in >> ExactSymbolSavedI{ ';', symbol };
  in >> dest.y;
  in >> ExactSymbolSavedI{ ')', symbol };

  if (!in && symbol != '\n')
  {
    fixStream(in);
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& chernikova::operator>>(std::istream& in, Polygon& dest)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  size_t count = 0;
  in >> count;

  if (!in)
  {
    fixStream(in);
    in.setstate(std::ios::failbit);
    return in;
  }

  using iter = std::istream_iterator< Point >;
  dest.points.clear();
  dest.points.reserve(count);
  std::copy(iter(in), iter(), std::back_inserter(dest.points));
  in.clear();

  if (count < 3 || dest.points.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  return in;
}

bool chernikova::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool chernikova::isOdd(const Polygon& polygon)
{
  return !isEven(polygon);
}

double chernikova::calcArea(const Point& lhs, const Point& rhs)
{
  return 0.5 * (lhs.x * rhs.y - rhs.x * lhs.y);
}

double chernikova::calcAreaForPoint(const Point& point)
{
  const Point* p1 = std::addressof(point);
  const Point* p2 = std::addressof(point) - 1;
  return calcArea(*p2, *p1);
}

double chernikova::getArea(const Polygon& polygon)
{
  std::vector < double > areas;
  areas.reserve(polygon.points.size() - 1);
  std::transform(polygon.points.begin() + 1, polygon.points.end(), std::back_inserter(areas), calcAreaForPoint);
  return std::abs(std::accumulate(areas.begin(), areas.end(), 0.0) +
    calcArea(polygon.points.back(), polygon.points.front()));
}

size_t chernikova::getVertexes(const Polygon& polygon)
{
  return polygon.points.size();
}

bool chernikova::isNecessaryVertex(const Polygon& polygon, size_t count)
{
  return polygon.points.size() == count;
}

std::vector< double > chernikova::getVectorArea(const std::vector< Polygon >& polygons)
{
  std::vector< double > areas;
  areas.reserve(polygons.size());
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), getArea);
  return areas;
}

std::vector< size_t > chernikova::getVectorVertexes(const std::vector< Polygon >& polygons)
{
  std::vector< size_t > vertexes;
  vertexes.reserve(polygons.size());
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes), getVertexes);
  return vertexes;
}

void chernikova::getAreaByPredicat(const std::vector< Polygon >& polygons, std::ostream& out, Predicat predicat)
{
  std::vector< Polygon > somePolygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(somePolygons), predicat);
  std::vector< double > areas = getVectorArea(somePolygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
}

void chernikova::getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  getAreaByPredicat(polygons, out, isEven);
}

void chernikova::getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  getAreaByPredicat(polygons, out, isOdd);
}

void chernikova::getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out)
{
  size_t count = polygons.size();
  std::vector< double > areas = getVectorArea(polygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0) / count << "\n";
}

void chernikova::getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  using namespace std::placeholders;
  std::vector< Polygon > vertexesPolygons;
  auto pred = std::bind(isNecessaryVertex, _1, count);
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vertexesPolygons), pred);
  std::vector< double > areas = getVectorArea(vertexesPolygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
}

void chernikova::getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< double > areas = getVectorArea(polygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << *(std::max_element(areas.begin(), areas.end())) << "\n";
}

void chernikova::getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< double > areas = getVectorArea(polygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << *(std::min_element(areas.begin(), areas.end())) << "\n";
}

void chernikova::getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< size_t > vertexes = getVectorVertexes(polygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << *(std::max_element(vertexes.begin(), vertexes.end())) << "\n";
}

void chernikova::getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< size_t > vertexes = getVectorVertexes(polygons);
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << *(std::min_element(vertexes.begin(), vertexes.end())) << "\n";
}

void chernikova::getCountByPredicat(const std::vector< Polygon >& polygons, std::ostream& out, Predicat predicat)
{
  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::count_if(polygons.begin(), polygons.end(), predicat) << "\n";
}

void chernikova::getCountEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  getCountByPredicat(polygons, out, isEven);
}

void chernikova::getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  getCountByPredicat(polygons, out, isOdd);
}

void chernikova::getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  using namespace std::placeholders;
  auto pred = std::bind(chernikova::isNecessaryVertex, _1, count);
  StreamGuard streamGuard(out);
  out << count_if(polygons.begin(), polygons.end(), pred) << "\n";
}

bool chernikova::isEqualPolygon(const Polygon& lhs, const Polygon& rhs)
{
  return (rhs.points == lhs.points);
}

void chernikova::echo(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
{
  using namespace std::placeholders;

  auto equal = std::bind(isEqualPolygon, _1, polygon);
  std::vector< Polygon > copies;
  copies.reserve(polygons.size());
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(copies), equal);

  StreamGuard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << copies.size() << "\n";

  std::copy(copies.begin(), copies.end(), std::back_inserter(polygons));
}

bool chernikova::hasIntersection(const Polygon& lhs, const Polygon& rhs)
{
  auto left = std::minmax_element(lhs.points.begin(), lhs.points.end());
  auto right = std::minmax_element(rhs.points.begin(), rhs.points.end());

  return (((*left.first <= *right.second) && (*left.second >= *right.first)) ||
  (((*right.first <= *left.second) && (*right.second >= *left.first))));
}

void chernikova::intersections(const std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
{
  using namespace std::placeholders;
  auto pred = std::bind(hasIntersection, _1, polygon);
  out << std::count_if(polygons.begin(), polygons.end(), pred) << "\n";
}

bool chernikova::isRightAngleByThreePoints(const Point* p1, const Point* p2, const Point* p3)
{
  long long int scalarMultiply = (p3->x - p2->x) * (p1->x - p2->x) + (p3->y - p2->y) * (p1->y - p2->y);
  return scalarMultiply == 0;
}

bool chernikova::isRightAngle(const Point& p)
{
  const Point* p1 = std::addressof(p);
  const Point* p2 = std::addressof(p) - 1;
  const Point* p3 = std::addressof(p) - 2;

  return isRightAngleByThreePoints(p1, p2, p3);
}

bool chernikova::hasRightAngle(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return false;
  }

  auto it = std::find_if(polygon.points.begin() + 2, polygon.points.end(), isRightAngle);

  if (it != polygon.points.end())
  {
    return true;
  }
  if (isRightAngleByThreePoints(&polygon.points.back(), &polygon.points.front(), &polygon.points.front() + 1))
  {
    return true;
  }
  if (isRightAngleByThreePoints(&polygon.points.back() - 1, &polygon.points.back(), &polygon.points.front()))
  {
    return true;
  }

  return false;
}

void chernikova::rightShapes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  size_t count = std::count_if(polygons.begin(), polygons.end(), hasRightAngle);
  out << count << "\n";
}
