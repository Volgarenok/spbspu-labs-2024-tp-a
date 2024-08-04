#include "polygon.hpp"

#include <algorithm>
#include <limits>
#include <iterator>

#include "../common/delimeter.hpp"

std::istream & rebdev::operator>>(std::istream & in, Point & point)
{
  in >> Delimeter{'('} >> point.x >> Delimeter{';'} >> point.y >> Delimeter{')'};
  return in;
}

std::istream & rebdev::operator>>(std::istream & in, Polygon & poly)
{
  size_t pointNum = 0;
  in >> pointNum;
  using inputItT = std::istream_iterator< Point >;
  Polygon newPoly;
  std::copy_n(inputItT{ in }, pointNum, std::back_inserter(newPoly.points));
  std::swap(newPoly, poly);
  if ((!in) && (!in.eof()))
  {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return in;
}
