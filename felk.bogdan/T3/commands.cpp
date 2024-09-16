#include "commands.hpp"

#include <map>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace felk
{
  double det(const Point& first, const Point& second)
  {
    return 0.5 * (first.x * second.y - first.y * second.x);
  }

  double getArea(const Polygon& poly)
  {
    std::vector< Point > temp;
    std::copy(++poly.points.begin(), poly.points.end(), std::back_inserter(temp));
    temp.push_back(*poly.points.begin());
    double area = 0.0;
    std::vector< double > results(poly.points.size());
    std::transform(poly.points.cbegin(), poly.points.cend(), temp.cbegin(), results.begin(), det);
    area = std::abs(std::accumulate(results.cbegin(), results.cend(), 0.0));
    return area;
  }

  bool compareArea(const Polygon& poly1, const Polygon& poly2)
  {
    return getArea(poly1) < getArea(poly2);
  }

  bool compareVertexes(const Polygon& poly1, const Polygon& poly2)
  {
    return poly1.points.size() < poly2.points.size();
  }

  bool isEven(const Polygon& poly)
  {
    return poly.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& poly)
  {
    return poly.points.size() % 2 != 0;
  }

  bool compareVertexesNum(const Polygon& poly, size_t n)
  {
    return poly.points.size() == n;
  }

  Polygon ifEqualEcho(const Polygon& poly1, const Polygon& poly2, std::vector< Polygon >& polys)
  {
    if (poly1.points == poly2.points)
    {
      polys.push_back(poly1);
    }
    return poly1;
  }

  bool isEqual(const Polygon& poly1, const Polygon& poly2)
  {
    return poly1.points == poly2.points;
  }

  size_t checkSeq(const std::vector< Polygon >& polys, size_t n, const Polygon& poly)
  {
    if (std::search_n(polys.cbegin(), polys.cend(), n, poly) != polys.cend())
    {
      return n;
    }
    else
    {
      return 0;
    }
  }

  bool comparePointX(const Point& point1, const Point& point2)
  {
    return point1.x < point2.x;
  }

  bool comparePointY(const Point& point1, const Point& point2)
  {
    return point1.y < point2.y;
  }

  bool comparePolyMinX(const Polygon& poly1, const Polygon& poly2)
  {
    auto min1 = std::min_element(poly1.points.begin(), poly1.points.end(), comparePointX);
    auto min2 = std::min_element(poly2.points.begin(), poly2.points.end(), comparePointX);
    return comparePointX(*min1, *min2);
  }

  bool comparePolyMaxX(const Polygon& poly1, const Polygon& poly2)
  {
    auto min1 = std::max_element(poly1.points.begin(), poly1.points.end(), comparePointX);
    auto min2 = std::max_element(poly2.points.begin(), poly2.points.end(), comparePointX);
    return comparePointX(*min1, *min2);
  }

  bool comparePolyMinY(const Polygon& poly1, const Polygon& poly2)
  {
    auto min1 = std::min_element(poly1.points.begin(), poly1.points.end(), comparePointY);
    auto min2 = std::min_element(poly2.points.begin(), poly2.points.end(), comparePointY);
    return comparePointY(*min1, *min2);
  }

  bool comparePolyMaxY(const Polygon& poly1, const Polygon& poly2)
  {
    auto min1 = std::max_element(poly1.points.begin(), poly1.points.end(), comparePointY);
    auto min2 = std::max_element(poly2.points.begin(), poly2.points.end(), comparePointY);
    return comparePointY(*min1, *min2);
  }

}

void felk::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  if (polys.empty())
  {
    throw std::invalid_argument("No polygons");
  }

  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    auto minArea = std::min_element(polys.cbegin(), polys.cend(), compareArea);
    out << getArea(*minArea) << "\n";
  }
  else
  {
    auto minVert = std::min_element(polys.cbegin(), polys.cend(), compareVertexes);
    out << minVert->points.size() << "\n";
  }
}

void felk::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  if (polys.empty())
  {
    throw std::invalid_argument("No polygons");
  }

  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    auto maxArea = std::max_element(polys.cbegin(), polys.cend(), compareArea);
    out << getArea(*maxArea) << "\n";
  }
  else
  {
    auto maxVert = std::max_element(polys.cbegin(), polys.cend(), compareVertexes);
    out << maxVert->points.size() << "\n";
  }
}

void felk::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  std::string argument;
  in >> argument;
  std::vector< Polygon > temp;
  if (argument == "EVEN")
  {
    std::copy_if(polys.begin(), polys.end(), std::back_inserter(temp), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(polys.begin(), polys.end(), std::back_inserter(temp), isOdd);
  }
  else if (argument == "MEAN")
  {
    temp = polys;
  }
  else
  {
    size_t n = 0;
    n = std::stoull(argument);
    if (n < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto filter = std::bind(compareVertexesNum, std::placeholders::_1, n);
    std::copy_if(polys.begin(), polys.end(), std::back_inserter(temp), filter);
  }
  std::vector< double > areas(temp.size());
  std::transform(temp.begin(), temp.end(), areas.begin(), getArea);
  double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
  if (argument == "MEAN")
  {
    if (polys.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    sum /= areas.size();
  }

  out << sum << "\n";
}

void felk::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  std::string argument;
  in >> argument;
  size_t res = 0;
  if (argument == "EVEN")
  {
    res = std::count_if(polys.cbegin(), polys.cend(), isEven);
  }
  else if (argument == "ODD")
  {
    res = std::count_if(polys.cbegin(), polys.cend(), isOdd);
  }
  else
  {
    size_t n = 0;
    n = std::stoull(argument);
    if (n < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto filter = std::bind(compareVertexesNum, std::placeholders::_1, n);
    res = std::count_if(polys.cbegin(), polys.cend(), filter);
  }
  out << res << "\n";
}

void felk::echo(std::istream& in, std::ostream& out, std::vector< Polygon >& polys)
{
  Polygon arg;
  in >> arg;
  if (!in || in.get() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  size_t rez = 0;
  auto check = std::bind(isEqual, std::placeholders::_1, arg);
  rez = std::count_if(polys.cbegin(), polys.cend(), check);

  std::vector< Polygon > temp;
  auto clone = std::bind(ifEqualEcho, std::placeholders::_1, std::cref(arg), std::ref(temp));
  std::transform(polys.begin(), polys.end(), std::back_inserter(temp), clone);
  polys = temp;
  out << rez << "\n";
}

void felk::maxSeq(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  Polygon arg;
  in >> arg;
  if (!in || in.get() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  size_t len = std::count(polys.cbegin(), polys.cend(), arg);
  std::vector< size_t > range(len);
  std::iota(range.begin(), range.end(), 1);
  auto fillLen = std::bind(checkSeq, std::cref(polys), std::placeholders::_1, std::cref(arg));
  std::vector< size_t > lens(polys.size());
  std::transform(range.cbegin(), range.cend(), lens.begin(), fillLen);
  out << *std::max_element(lens.cbegin(), lens.cend()) << "\n";
}

void felk::inFrame(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  Polygon arg;
  in >> arg;
  if (!in || in.get() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::pair< std::vector< Point >::iterator, std::vector< Point >::iterator > pairX;
  std::pair< std::vector< Point >::iterator, std::vector< Point >::iterator > pairY;
  pairX = std::minmax_element(arg.points.begin(), arg.points.end(), comparePointX);
  pairY = std::minmax_element(arg.points.begin(), arg.points.end(), comparePointY);
  auto minYArr = (std::min_element(polys.begin(), polys.end(), comparePolyMinY))->points;
  auto maxYArr = (std::max_element(polys.begin(), polys.end(), comparePolyMaxY))->points;
  auto minXArr = (std::min_element(polys.begin(), polys.end(), comparePolyMinX))->points;
  auto maxXArr = (std::max_element(polys.begin(), polys.end(), comparePolyMaxX))->points;
  int minFrameY = (std::min_element(minYArr.begin(), minYArr.end(), comparePointY))->y;
  int maxFrameY = (std::max_element(maxYArr.begin(), maxYArr.end(), comparePointY))->y;
  int minFrameX = (std::min_element(minXArr.begin(), minXArr.end(), comparePointX))->x;
  int maxFrameX = (std::max_element(maxXArr.begin(), maxXArr.end(), comparePointX))->x;
  bool checkY = (pairY.second->y <= maxFrameY) && (pairY.first->y >= minFrameY);
  if (checkY && (pairX.second->x <= maxFrameX) && (pairX.first->x >= minFrameX))
  {
    out << "<TRUE>" << "\n";
  }
  else
  {
    out << "<FALSE>" << "\n";
  }
}

