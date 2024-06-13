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
