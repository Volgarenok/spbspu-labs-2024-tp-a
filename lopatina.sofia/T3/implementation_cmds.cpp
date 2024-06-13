#include "implementation_cmds.hpp"
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include "polygon.hpp"

int multiplyX1Y2(const lopatina::Point & point, const lopatina::Point * const last)
{
  const lopatina::Point * ptr = std::addressof(point);
  if (ptr != last)
  {
    int x1 = (*ptr).x;
    int y2 = (*(++ptr)).y;
    return x1 * y2;
  }
  return 0;
}

int multiplyY1X2(const lopatina::Point & point, const lopatina::Point * const last)
{
  const lopatina::Point * ptr = std::addressof(point);
  if (ptr != last)
  {
    int y1 = (*ptr).y;
    int x2 = (*(++ptr)).x;
    return y1 * x2;
  }
  return 0;
}

double areaCount(const lopatina::Polygon & polygon)
{
  std::vector<lopatina::Point> points = polygon.points;
  lopatina::Point first_point = points.front();
  lopatina::Point last_point = points.back();
  lopatina::Point * last_point_ptr = std::addressof(points.back());
  std::vector<int> x1y2;
  std::vector<int> y1x2;
  using namespace std::placeholders;
  std::transform(std::begin(points), std::end(points), std::back_inserter(x1y2), std::bind(multiplyX1Y2, _1, last_point_ptr));
  std::transform(std::begin(points), std::end(points), std::back_inserter(y1x2), std::bind(multiplyY1X2, _1, last_point_ptr));
  double area = std::accumulate(std::begin(x1y2), std::end(x1y2),0) - std::accumulate(std::begin(y1x2), std::end(y1x2),0);
  area += last_point.x * first_point.y - last_point.y * first_point.x;
  return (std::abs(area)) / 2;
}

double sumArea(double init, const lopatina::Polygon & polygon)
{
  return init + areaCount(polygon);
}

bool isEven(const lopatina::Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool isOdd(const lopatina::Polygon & polygon)
{
  return (!isEven(polygon));
}

bool isNum(const lopatina::Polygon & polygon, size_t num)
{
  return (polygon.points.size() == num);
}

double lopatina::doAreaEven(const std::vector <Polygon> & figures)
{
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), isEven);
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  return sum;
}

double lopatina::doAreaOdd(const std::vector <Polygon> & figures)
{
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), isOdd);
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  return sum;
}

double lopatina::doAreaMean(const std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, sumArea);
  double sum_mean = sum / figures.size();
  return sum_mean;
}

double lopatina::doAreaNum(const std::vector <Polygon> & figures, size_t num)
{
  using namespace std::placeholders;
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), std::bind(isNum, _1, num));
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  return sum;
}

bool areaComp(const lopatina::Polygon & first, const lopatina::Polygon & second)
{
  return areaCount(first) < areaCount(second);
}

bool vertexesComp(const lopatina::Polygon & first, const lopatina::Polygon & second)
{
  return first.points.size() < second.points.size();
}

double lopatina::doMaxArea(const std::vector<Polygon> & figures)
{
  auto max_figure = std::max_element(std::begin(figures), std::end(figures), areaComp);
  return areaCount(*max_figure);
}

size_t lopatina::doMaxVertexes(const std::vector<Polygon> & figures)
{
  auto max_figure = std::max_element(std::begin(figures), std::end(figures), vertexesComp);
  return (*max_figure).points.size();
}

double lopatina::doMinArea(const std::vector<Polygon> & figures)
{
  auto min_figure = std::min_element(std::begin(figures), std::end(figures), areaComp);
  return areaCount(*min_figure);
}

size_t lopatina::doMinVertexes(const std::vector<Polygon> & figures)
{
  auto min_figure = std::min_element(std::begin(figures), std::end(figures), vertexesComp);
  return (*min_figure).points.size();
}

size_t lopatina::doCountEven(const std::vector<Polygon> & figures)
{
  return std::count_if(std::begin(figures), std::end(figures), isEven);
}

size_t lopatina::doCountOdd(const std::vector<Polygon> & figures)
{
  return std::count_if(std::begin(figures), std::end(figures), isOdd);
}

size_t lopatina::doCountNum(const std::vector<Polygon> & figures, size_t num)
{
  using namespace std::placeholders;
  return std::count_if(std::begin(figures), std::end(figures), std::bind(isNum, _1, num));
}

namespace lopatina
{
  struct CounterSequences
  {
    size_t counter{0};
    size_t operator()(const Polygon & polygon, const Polygon & given_polygon, const Polygon * const last);
  };
}

size_t lopatina::CounterSequences::operator()(const Polygon & polygon, const Polygon & given_polygon, const Polygon * const last)
{
  if (polygon == given_polygon)
  {
    ++counter;
    const lopatina::Polygon * ptr = std::addressof(polygon);
    if (ptr == last)
    {
      return counter;
    }
    return 0;
  }
  size_t counter_temp = counter;
  counter = 0;
  return counter_temp;
}

size_t lopatina::doMaxSeq(const std::vector<Polygon> & figures, const Polygon & given_figure)
{
  std::vector<size_t> counters;
  lopatina::CounterSequences counter;
  const lopatina::Polygon * last_pol_ptr = std::addressof(figures.back());
  using namespace std::placeholders;
  std::transform(std::begin(figures), std::end(figures), std::back_inserter(counters), std::bind(counter, _1, given_figure, last_pol_ptr));
  return *(std::max_element(std::begin(counters), std::end(counters)));
}

bool isEquivalent(const lopatina::Polygon & polygon1, const lopatina::Polygon & polygon2, const lopatina::Polygon & given_polygon)
{
  if ((polygon1 == polygon2) && (polygon1 == given_polygon))
  {
    return true;
  }
  return false;
}

size_t lopatina::doRmEcho(std::vector<Polygon> & figures, const Polygon & given_figure)
{
  size_t initial_size = figures.size();
  using namespace std::placeholders;
  auto iter = std::unique(std::begin(figures), std::end(figures), std::bind(isEquivalent, _1, _2, given_figure));
  figures.resize(std::distance(std::begin(figures), iter));
  return initial_size - figures.size();
}

namespace lopatina
{
  struct RightAngle
  {
    Point point1;
    Point point2;
    bool operator()(const Point & point3);
  };
}

bool lopatina::RightAngle::operator()(const Point & point3)
{
  Point vector1 = {point2.x - point1.x, point2.y - point1.y};
  Point vector2 = {point3.x - point1.x, point3.y - point1.y};
  point2 = point1;
  point1 = point3;
  return vector1.x * vector2.x + vector1.y * vector2.y == 0;
}

bool hasRightAngle(const lopatina::Polygon & polygon)
{
  lopatina::RightAngle angle{polygon.points[0], polygon.points[1]};
  return std::any_of(std::rbegin(polygon.points), std::rend(polygon.points), angle);
}

size_t lopatina::doRightShapes(const std::vector<Polygon> & figures)
{
  return std::count_if(std::begin(figures), std::end(figures), hasRightAngle);
}
