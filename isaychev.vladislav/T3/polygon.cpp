#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>

std::istream & isaychev::operator>>(std::istream & in, Polygon & p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using input_iter_t = std::istream_iterator< Point >;
  size_t amount = 0;
  std::vector< Point > temp;
  in >> amount;
  std::copy_n(input_iter_t{in}, amount, std::back_inserter(temp));
  if (in)
  {
    p.pnts = temp;
  }
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const Polygon & p)
{
  using output_iter_t = std::ostream_iterator< Point >;
  auto last_elem_iter = --p.pnts.cend();
  std::cout << p.pnts.size() << " ";
  std::copy(p.pnts.cbegin(), last_elem_iter, output_iter_t{out, " "});
  std::cout << *last_elem_iter;
  return out;
}

isaychev::AreaPartCalculator::AreaPartCalculator(const Point & rhs):
 prev_(rhs)
{}

double isaychev::AreaPartCalculator::operator()(const Point & p)
{
  double part = 0.5 * (prev_.x * p.y - p.x * prev_.y);
  prev_ = p;
  return part;
}

double isaychev::get_area(const Polygon & rhs)
{
  using namespace std::placeholders;
  using functor_t = AreaPartCalculator;
  std::vector< double > area_parts(rhs.pnts.size());
  auto get_part = std::bind(functor_t(rhs.pnts.back()), _1);
  std::transform(rhs.pnts.cbegin(), rhs.pnts.cend(), area_parts.begin(), get_part);
  return std::abs(std::accumulate(area_parts.cbegin(), area_parts.cend(), 0.0));
}

size_t isaychev::get_vertex(const Polygon & rhs)
{
  return rhs.pnts.size();
}
