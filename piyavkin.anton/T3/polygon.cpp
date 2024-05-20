#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <delimeter.hpp>

double piyavkin::detail::calculateArea::operator()(const Point& p, const Point& fixedP)
{
  double curr = 0.5 * std::abs((p.x - fixedP.x) * (changP.y - fixedP.y) - (changP.x - fixedP.x) * (p.y - fixedP.y));
  changP = p;
  return curr;
}

double piyavkin::getAreaPol(const Polygon& pol)
{
  std::vector< double > res;
  auto functor = std::bind(detail::calculateArea{pol.points[1]}, std::placeholders::_1, pol.points[0]);
  std::transform(pol.points.cbegin(), pol.points.cend(), std::back_inserter(res), functor);
  return std::accumulate(res.cbegin(), res.cend(), 0.0);
}

double piyavkin::getArea(const std::vector< Polygon >& pols)
{
  std::vector< double > res;
  std::transform(pols.cbegin(), pols.cend(), std::back_inserter(res), getAreaPol);
  return std::accumulate(res.cbegin(), res.cend(), 0.0);
}

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
  if (in) 
  {
    in >> std::noskipws;
    char c = 0;
    in >> c;
    if (c == '\n' || in.eof())
    {
      pol.points = temp;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> std::skipws;
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

bool piyavkin::operator<(const Point& lhs, const Point& rhs)
{
  return (lhs.x < rhs.x) && (lhs.y < rhs.y);
}
