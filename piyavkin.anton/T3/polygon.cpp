#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <delimeter.hpp>

std::istream& piyavkin::operator>>(std::istream& in, Polygon& pol)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countAngles = 0;
  in >> countAngles;
  const size_t minAngles = 3;
  if (countAngles < minAngles)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  temp.reserve(countAngles);
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{in}, countAngles, std::back_inserter(temp));
  if (temp.size() == countAngles)
  {
    pol.points = temp;
  }
  return in;
}

std::istream& piyavkin::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp{0,0};
  using dc = DelimeterChar;
  in >> dc{'('} >> temp.x >> dc{';'} >> temp.y >> dc {')'};
  if (in)
  {
    p = temp;
  }
  return in;
}