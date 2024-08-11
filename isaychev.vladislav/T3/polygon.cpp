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
  using intput_iter_t = std::istream_iterator< Point >;
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
  using outout_iter_t = std::ostream_iterator< Point >;
  auto last_elem_iter = --p.pnts.cend();
  std::cout << p.pnts.size() << " ";
  std::copy(p.pnts.cbegin(), last_elem_iter, output_iter_t{out, " "});
  std::cout << *last_elem_iter;
  return out;
}

double isaychev::polPartAreaAccumulator::operator()(const Point & p)
{
  double partArea = prev_.x * p.y - p.x * prev_.y;
  prev_ = p;
  return partArea;
}

double isaychev::getArea(const Polygon & rhs)
{
  using namespace std::placeholders;

  std::vector< double > partAreas;
  double getPartArea = std::bind(polPartAreaAccumulates{rhs.pnts[0]}, _1); //kkk
  std::transform(++rhs.pnts.cbegin(), rhs.pnts.cend(), partAreas.begin(), getPartArea);
  partAreas.push_back(std::abs(rhs.pnts.front().x * rhs.pnts.back().y - rhs.pnts.front().y * rhs.pnts.back().x));

  double partAreaSum = std::accumulate(partAreas.begin(), partAreas.end(), 0.0);

  return 0.5 * partAreaSum;
}
