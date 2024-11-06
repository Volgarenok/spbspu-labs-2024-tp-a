#include "commands.hpp"
#include <algorithm>

namespace petuhov
{
  int same_count(const std::vector<Polygon> &polygons, const Polygon &target)
  {
    return std::count(polygons.begin(), polygons.end(), target);
  }

  bool is_permutation(const Polygon &a, const Polygon &b)
  {
    if (a.points.size() != b.points.size())
    {
      return false;
    }
    std::vector< Point > points_a = a.points;
    std::vector< Point > points_b = b.points;

    std::sort(points_a.begin(), points_a.end(), [](const Point &p1, const Point &p2) {
      return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
    });
    std::sort(points_b.begin(), points_b.end(), [](const Point &p1, const Point &p2) {
      return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
    });

    return points_a == points_b;
  }

  int perms_count(const std::vector<Polygon> &polygons, const Polygon &target)
  {
    return std::count_if(polygons.begin(), polygons.end(), [&target](const Polygon &poly) {
      return is_permutation(poly, target);
    });
  }

  bool has_right_angle(const Polygon &poly)
  {
    auto size = poly.points.size();
    if (size < 3)
    {
      return false;
    }
    for (size_t i = 0; i < size; ++i)
    {
      Point a = poly.points[i];
      Point b = poly.points[(i + 1) % size];
      Point c = poly.points[(i + 2) % size];

      int dx1 = b.x_ - a.x_;
      int dy1 = b.y_ - a.y_;
      int dx2 = c.x_ - b.x_;
      int dy2 = c.y_ - b.y_;

      if (dx1 * dx2 + dy1 * dy2 == 0)
      {
        return true;
      }
    }
    return false;
  }

  int right_shapes_count(const std::vector<Polygon> &polygons)
  {
    return std::count_if(polygons.begin(), polygons.end(), [](const Polygon &poly){
      return has_right_angle(poly);
    });
  }
}
