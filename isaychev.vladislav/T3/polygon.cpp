#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <functional>

std::istream & isaychev::operator>>(std::istream & in, Polygon & p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using input_iter_t = std::istream_iterator< Point >;
  std::vector< Point > temp;
  size_t amount = 0;
  in >> amount;
  if (amount < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::copy_n(input_iter_t{in}, amount, std::back_inserter(temp));
  if (in && amount == temp.size())
  {
    p.pnts = std::move(temp);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const Polygon & p)
{
  using output_iter_t = std::ostream_iterator< Point >;
  out << p.pnts.size() << " ";
  std::copy_n(p.pnts.cbegin(), p.pnts.size() - 1, output_iter_t{out, " "});
  out << p.pnts.back();
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

isaychev::EqualCounter::EqualCounter(const Polygon & rhs):
 expected_(rhs),
 count_(0)
{}

size_t isaychev::EqualCounter::operator()(const Polygon & rhs)
{
  if (!is_equal(expected_, rhs))
  {
    count_ = 0;
    return count_;
  }
  ++count_;
  return count_;
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

bool isaychev::is_even(const Polygon & rhs)
{
  return (rhs.pnts.size() % 2 ) == 0;
}

bool isaychev::is_odd(const Polygon & rhs)
{
  return !is_even(rhs);
}

bool isaychev::is_right_size(const Polygon & rhs, size_t expected)
{
  return rhs.pnts.size() == expected;
}

bool isaychev::is_equal(const Polygon & pol, const Polygon & rhs)
{
  return pol.pnts == rhs.pnts;
}

bool isaychev::has_intersections(const Polygon & pol, const Polygon & rhs)
{
  auto rect1 = std::minmax_element(pol.pnts.cbegin(), pol.pnts.cend());
  auto rect2 = std::minmax_element(rhs.pnts.cbegin(), rhs.pnts.cend());
  return !((*rect1.second < *rect2.first) || (*rect2.second < *rect1.first));
}
