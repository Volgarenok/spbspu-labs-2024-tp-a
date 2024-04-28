#include "polygon.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "point.hpp"

std::istream& novikov::operator>>(std::istream& in, Polygon& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::size_t n;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  points.reserve(n);
  std::copy_n(std::istream_iterator< Point >{ in }, n, std::back_inserter(points));
  if (in)
  {
    rhs.points = std::move(points);
  }

  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Polygon& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << rhs.points.size() << " ";
  std::copy(rhs.points.cbegin(), rhs.points.cend(), std::ostream_iterator< Point >{out, " "});
  return out;
}

double novikov::get_area(const Polygon& rhs)
{
  using namespace std::placeholders;
  auto acc_area = std::bind(AreaAccumulator{ rhs.points[1] }, _1, _2, rhs.points[0]);
  return std::accumulate(rhs.points.cbegin(), rhs.points.cend(), 0.0, acc_area);
}
