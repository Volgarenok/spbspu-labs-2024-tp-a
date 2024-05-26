#include <vector>
#include "Polygon.hpp"

namespace yakshieva
{
  struct PolygonComparator
  {
    const Polygon& target;
    bool operator()(const Polygon& p1, const Polygon& p2) const;
  };
  size_t removeConsecutiveDuplicates(std::vector< Polygon >& polygons, const Polygon& target);
  void duplicateEntries(std::vector<Polygon>& p, const Polygon& targetP);
}
