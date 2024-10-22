#include "commands.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <scopeguard.hpp>
#include "polygon.hpp"

namespace
{
  double calcArea(const agarkov::Point & left, const agarkov::Point & right)
  {
    return 0.5 * (left.x_ * right.y_ - right.x_ * left.y_);
  }

  double getArea(const agarkov::Polygon & polygon)
  {
    double res = 0.0;
    std::vector< double > values(polygon.points_.size());
    std::transform(polygon.points_.begin(), --polygon.points_.end(), ++polygon.points_.begin(), values.begin(), calcArea);
    res = std::accumulate(values.begin(), values.end(), 0.0);
    long long x1 = polygon.points_.back().x_;
    long long y1 = polygon.points_.back().y_;
    long long x2 = polygon.points_.front().x_;
    long long y2 = polygon.points_.front().y_;
    res += 0.5 * (x1 * y2 - y1 * x2);
    return std::abs(res);
  }

  double sumArea(double cur, const agarkov::Polygon& polygon)
  {
    return cur + getArea(polygon);
  }

  bool isEven(const agarkov::Polygon& polygon)
  {
    return polygon.points_.size() % 2 == 0;
  }

  bool isOdd(const agarkov::Polygon& polygon)
  {
    return !isEven(polygon);
  }
  bool isNecessaryVertex(const agarkov::Polygon& polygon, size_t count)
  {
    return polygon.points_.size() == count;
  }
  double chooseGreatereArea(double cur, const agarkov::Polygon& polygon)
  {
    double area = getArea(polygon);
    return (cur > area) ? cur : area;
  }
  size_t chooseGreatereVertexes(double cur, const agarkov::Polygon& polygon)
  {
    size_t count = polygon.points_.size();
    return (cur > count) ? cur : count;
  }
}

void agarkov::getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< Polygon > even_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), isEven);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, sumArea) << "\n";
}

void agarkov::getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  std::vector< Polygon > odd_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), isOdd);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(odd_polygons.begin(), odd_polygons.end(), 0.0, sumArea) << "\n";
}

void agarkov::getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("invalid arg");
  }
  size_t count = polygons.size();
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, sumArea) / count << "\n";
}

void agarkov::getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  if (count < 3)
  {
    throw std::logic_error("invalid arg");
  }
  std::vector< Polygon > vertexes_polygons;
  using namespace std::placeholders;
  auto pred = std::bind(isNecessaryVertex, _1, count);
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vertexes_polygons), pred);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(vertexes_polygons.begin(), vertexes_polygons.end(), 0.0, sumArea) << "\n";
}

void agarkov::getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("invalid arg");
  }
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, chooseGreatereArea) << "\n";
}

void agarkov::getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("invalid arg");
  }
  iofmtguard iofmtguard(out);
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, chooseGreatereVertexes) << "\n";
}
