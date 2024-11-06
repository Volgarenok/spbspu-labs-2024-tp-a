#include "commands.hpp"
#include <algorithm>
#include <vector>
#include <numeric>

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



  bool has_right_angle(const Polygon &poly) {
    size_t size = poly.points.size();
    if (size < 3) {
      return false;
    }

    for (size_t i = 0; i < size; ++i) {
      const Point &a = poly.points[i];
      const Point &b = poly.points[(i + 1) % size];
      const Point &c = poly.points[(i + 2) % size];

      int dx1 = b.x_ - a.x_;
      int dy1 = b.y_ - a.y_;
      int dx2 = c.x_ - b.x_;
      int dy2 = c.y_ - b.y_;

      if (dx1 * dx2 + dy1 * dy2 == 0) {
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

  bool is_permutation(const Polygon &a, const Polygon &b) {
    if (a.points.size() != b.points.size()) {
      return false;
    }

    std::vector<Point> sorted_a = a.points;
    std::vector<Point> sorted_b = b.points;

    std::sort(sorted_a.begin(), sorted_a.end(), [](const Point &p1, const Point &p2) {
      return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
    });

    std::sort(sorted_b.begin(), sorted_b.end(), [](const Point &p1, const Point &p2) {
      return std::tie(p1.x_, p1.y_) < std::tie(p2.x_, p2.y_);
    });

    return sorted_a == sorted_b;
  }

  double calculate_area(const Polygon& poly) {
    double area = 0.0;
    size_t size = poly.points.size();
    for (size_t i = 0; i < size; ++i) {
      const Point& p1 = poly.points[i];
      const Point& p2 = poly.points[(i + 1) % size];
      area += (p1.x_ * p2.y_ - p2.x_ * p1.y_);
    }
    return std::abs(area) / 2.0;
  }

  double sum_area(const std::vector<Polygon>& polygons, bool even) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0, [even](double sum, const Polygon& poly) {
      return (poly.points.size() % 2 == 0) == even ? sum + calculate_area(poly) : sum;
    });
  }

  double mean_area(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::runtime_error("No polygons available");
    }

    double total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double sum, const Polygon& poly) {
      return sum + calculate_area(poly);
    });

    return total_area / polygons.size();
  }

  double sum_area_by_vertex_count(const std::vector<Polygon>& polygons, int vertex_count) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0, [vertex_count](double sum, const Polygon& poly) {
      return static_cast<int>(poly.points.size()) == vertex_count ? sum + calculate_area(poly) : sum;
    });
  }

  int max_vertex_count(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::runtime_error("No polygons available");
    }

    return std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
      return a.points.size() < b.points.size();
    })->points.size();
  }

  double max_area(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::runtime_error("No polygons available");
    }

    return std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
      return calculate_area(a) < calculate_area(b);
    })->points.size();
  }

  int min_vertex_count(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::runtime_error("No polygons available");
    }

    return std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
      return a.points.size() < b.points.size();
    })->points.size();
  }

  double min_area(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
      throw std::runtime_error("No polygons available");
    }

    return std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
      return calculate_area(a) < calculate_area(b);
    })->points.size();
  }

  int count_by_vertex_parity(const std::vector<Polygon>& polygons, bool even) {
    return std::count_if(polygons.begin(), polygons.end(), [even](const Polygon& poly) {
      return (poly.points.size() % 2 == 0) == even;
    });
  }

  int count_by_vertex_count(const std::vector<Polygon>& polygons, int vertex_count) {
    return std::count_if(polygons.begin(), polygons.end(), [vertex_count](const Polygon& poly) {
      return static_cast<int>(poly.points.size()) == vertex_count;
    });
  }
}
