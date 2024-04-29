#include "geometry.hpp"
#include <istream>
#include <iterator>
#include <vector>

std::istream& demidenko::readPolygons(std::istream& in, std::vector< Polygon >& polygons)
{
  std::istream::sentry sentry{ in };
  if (!in)
  {
    return in;
  }

  using InputIterator = std::istream_iterator< demidenko::Polygon >;
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
    }
    std::copy(InputIterator{ in }, InputIterator{}, std::back_inserter(polygons));
  }
  return in;
}
