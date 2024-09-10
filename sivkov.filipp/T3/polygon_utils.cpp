#include "polygon_utils.hpp"
#include <algorithm>

namespace sivkov
{
  bool isPointCountEqual(const Polygon& shape, size_t num)
  {
    return num == shape.points.size();
  }

  bool isPerms(const Polygon& first, const Polygon& second)
  {
    if (first.points.size() != second.points.size())
    {
      return false;
    }
    return std::is_permutation(first.points.cbegin(), first.points.cend(), second.points.cbegin());
  }
}
