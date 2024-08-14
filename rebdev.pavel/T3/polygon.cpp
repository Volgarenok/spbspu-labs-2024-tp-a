#include "polygon.hpp"

#include <algorithm>
#include <limits>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <string>

#include "../common/delimeter.hpp"

std::istream & rebdev::operator>>(std::istream & in, Point & point)
{
  in >> Delimeter{'('} >> point.x >> Delimeter{';'} >> point.y >> Delimeter{')'};
  return in;
}
std::istream & rebdev::operator>>(std::istream & in, Polygon & poly)
{
  poly.points.clear();
  std::string str;
  std::getline(in, str);
  if (str.empty())
  {
    return in;
  }
  std::stringstream inStr(str);
  size_t pointNum = 0;
  inStr >> pointNum;
  if (inStr.eof() || (pointNum < 3))
  {
    return in;
  }
  using inputItT = std::istream_iterator< Point >;
  Polygon newPoly;
  newPoly.points.insert(newPoly.points.begin(), inputItT{ inStr }, inputItT{});
  if ((inStr.fail() && !inStr.eof()) || (pointNum < 3) || (newPoly.points.size() != pointNum))
  {
    newPoly.points.clear();
  }
  std::swap(newPoly, poly);
  return in;
}
