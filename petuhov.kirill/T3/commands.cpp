#include "commands.hpp"
#include <algorithm>
#include <vector>

namespace petuhov
{
  int same_count(const std::vector< Polygon > &polygons, const Polygon &target) {
    std::vector< Point > normalized_target = normalize(target);

    return std::count_if(polygons.begin(), polygons.end(), [&normalized_target](const Polygon &poly) {
      return normalize(poly) == normalized_target;
    });
  }

  int perms_count(const std::vector<Polygon> &polygons, const Polygon &target) {
    return std::count_if(polygons.begin(), polygons.end(), [&target](const Polygon &poly) {
      return is_permutation(poly, target);
    });
  }



  bool has_right_angle(const Polygon &poly)
  {
    size_t size = poly.points.size();
    if (size < 3) {
      return false;
    }

    int right_angle_count = 0;
    for (size_t i = 0; i < size; ++i) {
      Point a = poly.points[i];
      Point b = poly.points[(i + 1) % size];
      Point c = poly.points[(i + 2) % size];

      int dx1 = b.x_ - a.x_;
      int dy1 = b.y_ - a.y_;
      int dx2 = c.x_ - b.x_;
      int dy2 = c.y_ - b.y_;

      if (dx1 * dx2 + dy1 * dy2 == 0) {
        right_angle_count++;
        if (right_angle_count >= 2) {
          return true;
        }
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

  std::vector<Point> normalize(const Polygon &polygon) {
    std::vector<Point> normalized_points = polygon.points;

    Point min_point = *std::min_element(normalized_points.begin(), normalized_points.end(), [](const Point &p1, const Point &p2) {
      return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
    });

    for (Point &point : normalized_points) {
      point.x_ -= min_point.x_;
      point.y_ -= min_point.y_;
    }

    std::sort(normalized_points.begin(), normalized_points.end(), [](const Point &p1, const Point &p2) {
      return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
    });

    return normalized_points;
  }

  bool is_permutation(const petuhov::Polygon &a, const petuhov::Polygon &b) {
  if (a.points.size() != b.points.size()) {
    return false;
  }

  std::vector<petuhov::Point> sorted_a = a.points;
  std::vector<petuhov::Point> sorted_b = b.points;

  std::sort(sorted_a.begin(), sorted_a.end(), [](const petuhov::Point &p1, const petuhov::Point &p2) {
    return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
  });

  std::sort(sorted_b.begin(), sorted_b.end(), [](const petuhov::Point &p1, const petuhov::Point &p2) {
    return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
  });

  return sorted_a == sorted_b;
}

}
