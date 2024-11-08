#include "Commands.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <StreamGuard.h>
#include "DataStruct.h"

namespace stepanov
{
  bool isEven(const Polygon& polygon)
  {
    return polygon.points_.size() % 2 == 0;
  }

  bool isOdd(const Polygon& polygon)
  {
    return !isEven(polygon);
  }

  double calcArea(const Point & left, const Point & right)
  {
    return 0.5 * (left.x_ * right.y_ - right.x_ * left.y_);
  }

  double getArea(const Polygon & polygon)
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

  double sumArea(double cur, const Polygon& polygon)
  {
    return cur + getArea(polygon);
  }

  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > even_polygons;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), isEven);
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, sumArea) << "\n";
  }

  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > odd_polygons;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), isOdd);
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(odd_polygons.begin(), odd_polygons.end(), 0.0, sumArea) << "\n";
  }

  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("invalid arg");
    }
    size_t count = polygons.size();
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygons.begin(), polygons.end(), 0.0, sumArea) / count << "\n";
  }

  bool isNecessaryVertexCount(const Polygon& polygon, size_t count)
  {
    return polygon.points_.size() == count;
  }

  void getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
  {
      if (count < 3)
    {
      throw std::logic_error("Incorrect input");
    }
    std::vector< Polygon > vertexes_polygons;
    using namespace std::placeholders;
    auto pred = std::bind(isNecessaryVertexCount, _1, count);
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vertexes_polygons), pred);
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(vertexes_polygons.begin(), vertexes_polygons.end(), 0.0, sumArea) << "\n";
  }

  double chooseGreatereArea(double cur, const Polygon& polygon)
  {
    double area = getArea(polygon);
    return (cur > area) ? cur : area;
  }

  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Incorrect input");
    }
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygons.begin(), polygons.end(), 0.0, chooseGreatereArea) << "\n";
  }

  size_t chooseGreatereVertexes(double cur, const Polygon& polygon)
  {
    size_t count = polygon.points_.size();
    return (cur > count) ? cur : count;
  }

  void getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Incorrect input");
    }
    StreamGuard format(out);
    out << std::accumulate(polygons.begin(), polygons.end(), 0.0, chooseGreatereVertexes) << "\n";
  }

  double chooseLessArea(double cur, const Polygon& polygon)
  {
    double area = getArea(polygon);
    return (cur < area) ? cur : area;
  }

  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Incorrect input");
    }
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygons.begin(), polygons.end(), getArea(polygons.front()), chooseLessArea) << "\n";
  }

  size_t chooseLessVertexes(double cur, const Polygon& polygon)
  {
    size_t count = polygon.points_.size();
    return (cur < count) ? cur : count;
  }

  void getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Incorrect input");
    }
    StreamGuard format(out);
    out << std::accumulate(polygons.begin(), polygons.end(), polygons.front().points_.size(), chooseLessVertexes) << "\n";
  }

  void getCountEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::count_if(polygons.begin(), polygons.end(), isEven) << "\n";
  }

  void getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::count_if(polygons.begin(), polygons.end(), isOdd) << "\n";
  }

  void getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
  {
    if (count < 3)
    {
      throw std::logic_error("Incorrect input");
    }
    using namespace std::placeholders;
    auto pred = std::bind(isNecessaryVertexCount, _1, count);
    StreamGuard format(out);
    out << count_if(polygons.begin(), polygons.end(), pred) << "\n";
  }

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs, const Polygon& polygon)
  {
    return (rhs == lhs) && (rhs == polygon);
  }

  void rmEcho(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
  {
    using namespace std::placeholders;
    auto pred = std::bind(isEqualPolygon, _1, _2, polygon);
    auto new_end = std::unique(polygons.begin(), polygons.end(), pred);
    size_t res = std::distance(new_end, polygons.end());
    polygons.erase(new_end, polygons.end());
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << res << "\n";
  }

  double findLength(const Point& point1, const Point& point2)
  {
    double first_square = (point1.x_ - point2.x_) * (point1.x_ - point2.x_);
    double second_square = (point1.y_ - point2.y_) * (point1.y_ - point2.y_);
    return std::sqrt(first_square + second_square);
  }

  bool isRect(const Polygon& polygon)
  {
    if (polygon.points_.size() != 4)
    {
      return false;
    }
    double first = findLength(polygon.points_[0], polygon.points_[1]);
    double second = findLength(polygon.points_[1], polygon.points_[2]);
    double third = findLength(polygon.points_[2], polygon.points_[3]);
    double fourth = findLength(polygon.points_[3], polygon.points_[0]);
    double diagonal = findLength(polygon.points_[0], polygon.points_[2]);
    bool is_rect_triangle = std::sqrt(first * first + second * second) == diagonal;
    return (first == third && second == fourth && is_rect_triangle);
  }

  void getRects(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    StreamGuard format(out);
    out << std::fixed << std::setprecision(1);
    out << std::count_if(polygons.begin(), polygons.end(), isRect) << '\n';
  }
}
