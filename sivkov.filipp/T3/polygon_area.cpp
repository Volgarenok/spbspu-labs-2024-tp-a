#include "polygon_area.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

namespace sivkov
{
  struct AreaFunctor
  {
    double operator()(const Point& a, const Point& b) const
    {
      return (a.x * b.y) - (b.x * a.y);
    }
  };

  double calculateArea(const Polygon& polygon)
  {
    if (polygon.points.size() < 3)
    {
      return 0.0;
    }
    std::vector<double> areas(polygon.points.size());
    std::transform(polygon.points.begin(), polygon.points.end() - 1, polygon.points.begin() + 1, areas.begin(), AreaFunctor());
    AreaFunctor func;
    areas.push_back(func(polygon.points.back(), polygon.points.front()));
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    return std::abs(area) / 2.0;
  }

  void maxArea(std::ostream& out, const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("No polygons provided");
    }

    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), calculateArea);
    auto max_area_it = std::max_element(areas.begin(), areas.end());
    out << std::fixed << std::setprecision(1) << *max_area_it;
  }

  void minArea(std::ostream& out, const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("No polygons provided");
    }

    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), calculateArea);
    auto min_area_it = std::min_element(areas.begin(), areas.end());
    out << std::fixed << std::setprecision(1) << *min_area_it;
  }
}
