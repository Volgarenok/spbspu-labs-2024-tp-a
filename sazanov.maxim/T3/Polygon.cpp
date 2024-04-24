#include "Polygon.hpp"
#include <iostream>
#include <iterator>
#include "Point.hpp"

std::istream& sazanov::operator>>(std::istream& in, sazanov::Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::size_t vertices = 0;
  in >> vertices;
  if (vertices < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;
  temp.reserve(vertices);
  using input_it_t = std::istream_iterator< Point >;
  std::copy(
    input_it_t{std::cin},
    input_it_t{},
    std::back_inserter(temp)
  );
  if (temp.size() == vertices)
  {
    polygon.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
