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

  double chooseLessArea(double cur, const agarkov::Polygon& polygon)
  {
    double area = getArea(polygon);
    return (cur < area) ? cur : area;
  }

  size_t chooseLessVertexes(double cur, const agarkov::Polygon& polygon)
  {
    size_t count = polygon.points_.size();
    return (cur < count) ? cur : count;
  }

  bool isCompatiblePoints(const agarkov::Point& lhs, const agarkov::Point& rhs, const long long dif_x, const long long dif_y)
  {
    return ((lhs.x_ - rhs.x_) == dif_x) && ((lhs.y_ - rhs.y_) == dif_y);
  }

  bool isCompatiblePolygons(const agarkov::Polygon& lhs, const agarkov::Polygon& rhs)
  {
    size_t size = lhs.points_.size();
    if (size != rhs.points_.size())
    {
      return false;
    }
    const long long dif_x = lhs.points_.front().x_ - rhs.points_.front().x_;
    const long long dif_y = lhs.points_.front().y_ - rhs.points_.front().y_;
    std::vector< bool > result(size);
    using namespace std::placeholders;
    auto binary_op = std::bind(isCompatiblePoints, _1, _2, dif_x, dif_y);
    std::transform(lhs.points_.begin(), lhs.points_.end(), rhs.points_.begin(), result.begin(), binary_op);
    return result.size() == std::accumulate(result.begin(), result.end(), 0ull);
  }
  double findSide(const agarkov::Point& point1, const agarkov::Point& point2)
  {
    double firstSquare = (point1.x_ - point2.x_) * (point1.x_ - point2.x_);
    double secondSquare = (point1.y_ - point2.y_) * (point1.y_ - point2.y_);
    return std::sqrt(firstSquare + secondSquare);
  }

  bool isRectangle(const agarkov::Polygon& polygon)
  {
    if (polygon.points_.size() != 4ull)
    {
      return false;
    }
    double first = findSide(polygon.points_[0], polygon.points_[1]);
    double second = findSide(polygon.points_[1], polygon.points_[2]);
    double third = findSide(polygon.points_[2], polygon.points_[3]);
    double fourth = findSide(polygon.points_[3], polygon.points_[0]);
    double diagonal = findSide(polygon.points_[0], polygon.points_[2]);
    bool isRectangularTriangle = std::sqrt(first * first + second * second) == diagonal;
    return (first == third && second == fourth && isRectangularTriangle);
  }

  size_t getCountInSequence(const agarkov::Polygon& polygon, const agarkov::Polygon& input_polygon, const std::vector< size_t >& sequence)
  {
    if (!(polygon == input_polygon))
    {
      return 0;
    }
    if (sequence.empty())
    {
      return 1;
    }
    return sequence.back() + 1;
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

void agarkov::getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("invalid arg");
  }
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(polygons.begin(), polygons.end(), getArea(polygons.front()), chooseLessArea) << "\n";
}

void agarkov::getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("invalid arg");
  }
  iofmtguard iofmtguard(out);
  out << std::accumulate(polygons.begin(), polygons.end(), polygons.front().points_.size(), chooseLessVertexes) << "\n";
}

void agarkov::getCountEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::count_if(polygons.begin(), polygons.end(), isEven) << "\n";
}

void agarkov::getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << std::count_if(polygons.begin(), polygons.end(), isOdd) << "\n";
}

void agarkov::getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  if (count < 3)
  {
    throw std::logic_error("invalid arg");
  }
  using namespace std::placeholders;
  auto pred = std::bind(isNecessaryVertex, _1, count);
  iofmtguard iofmtguard(out);
  out << count_if(polygons.begin(), polygons.end(), pred) << "\n";
}

void agarkov::getSame(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
{
  using namespace std::placeholders;
  auto pred = std::bind(isCompatiblePolygons, polygon, _1);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << count_if(polygons.begin(), polygons.end(), pred) << "\n";
}

void agarkov::getRects(const std::vector< Polygon >& polygons, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(), isRectangle) << '\n';
}


void agarkov::getMaxSequence(const std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("invalid arg");
  }
  std::vector< size_t > sequence;
  sequence.reserve(polygons.size());
  using namespace std::placeholders;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(sequence),
    std::bind(getCountInSequence, _1, polygon, std::cref(sequence)));
  out << *std::max_element(sequence.begin(), sequence.end());
}
