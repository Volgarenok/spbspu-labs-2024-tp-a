#include "Commands.h"
#include <vector>
#include <ostream>
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
  }
}
