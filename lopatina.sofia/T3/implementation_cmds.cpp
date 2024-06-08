#include "implementation_cmds.hpp"
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include "polygon.hpp"

int multi1(const lopatina::Point & point, const lopatina::Point * const last)
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

int multi2(const lopatina::Point & point, const lopatina::Point * const last)
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
  lopatina::Point * last_point = std::addressof(points.back());
  using namespace std::placeholders;
  std::vector<int> x1y2;
  std::vector<int> y1x2;
  std::transform(std::begin(points), std::end(points), std::back_inserter(x1y2), std::bind(multi1, _1, last_point));
  std::transform(std::begin(points), std::end(points), std::back_inserter(y1x2), std::bind(multi2, _1, last_point));
  double area = (std::abs(std::accumulate(std::begin(x1y2), std::end(x1y2),0) - std::accumulate(std::begin(y1x2), std::end(y1x2),0))) / 2;
  return area;
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

void lopatina::areaEven(const std::vector <Polygon> & figures)
{
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), isEven);
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  std::cout << "AREA EVEN: " << sum << '\n';
}

void lopatina::areaOdd(const std::vector <Polygon> & figures)
{
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), isOdd);
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  std::cout << "AREA ODD: " << sum << '\n';
}

void lopatina::areaMean(const std::vector <Polygon> & figures)
{
  using namespace std::placeholders;
  double sum = std::accumulate(std::begin(figures), std::end(figures), 0, sumArea);
  double sum_mean = sum / figures.size();
  std::cout << "AREA MEAN: " << sum_mean << '\n';
}

void lopatina::areaNum(const std::vector <Polygon> & figures, size_t num)
{
  using namespace std::placeholders;
  std::vector <Polygon> filter;
  std::copy_if(std::begin(figures), std::end(figures), std::back_inserter(filter), std::bind(isNum, _1, num));
  double sum = std::accumulate(std::begin(filter), std::end(filter), 0, sumArea);
  std::cout << "AREA NUM: " << sum << '\n';
}

bool areaComp(const lopatina::Polygon & first, const lopatina::Polygon & second)
{
  return areaCount(first) < areaCount(second);
}

bool vertexesComp(const lopatina::Polygon & first, const lopatina::Polygon & second)
{
  return first.points.size() < second.points.size();
}

void lopatina::maxArea(const std::vector<Polygon> & figures)
{
  auto max_figure = std::max_element(std::begin(figures), std::end(figures), areaComp);
  double max_area = areaCount(*max_figure);
  std::cout << "MAX AREA: " << max_area << '\n';
}

void lopatina::maxVertexes(const std::vector<Polygon> & figures)
{
  auto max_figure = std::max_element(std::begin(figures), std::end(figures), vertexesComp);
  double max_vertexes = (*max_figure).points.size();
  std::cout << "MAX VERTEXES: " << max_vertexes << '\n';
}

void lopatina::minArea(const std::vector<Polygon> & figures)
{
  auto min_figure = std::min_element(std::begin(figures), std::end(figures), areaComp);
  double min_area = areaCount(*min_figure);
  std::cout << "MIN AREA: " << min_area << '\n';
}

void lopatina::minVertexes(const std::vector<Polygon> & figures)
{
  auto min_figure = std::min_element(std::begin(figures), std::end(figures), vertexesComp);
  double min_vertexes = (*min_figure).points.size();
  std::cout << "MIN VERTEXES: " << min_vertexes << '\n';
}

void lopatina::countEven(const std::vector<Polygon> & figures)
{
  size_t counter = std::count_if(std::begin(figures), std::end(figures), isEven);
  std::cout << "COUNT EVEN: " << counter << '\n';
}

void lopatina::countOdd(const std::vector<Polygon> & figures)
{
  size_t counter = std::count_if(std::begin(figures), std::end(figures), isOdd);
  std::cout << "COUNT ODD: " << counter << '\n';
}

void lopatina::countNum(const std::vector<Polygon> & figures, size_t num)
{
  using namespace std::placeholders;
  size_t counter = std::count_if(std::begin(figures), std::end(figures), std::bind(isNum, _1, num));
  std::cout << "COUNT NUM: " << counter << '\n';
}
