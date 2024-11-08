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

  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > even_polygons;
  }
}
