#include "polygon.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>

std::istream & lebedev::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t points_num = 0;
  input >> points_num;
  if (points_num < 3)
  {
    input.setstate(std::ios::failbit);
  }
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >(input), points_num, std::back_inserter(points));
  if (input)
  {
    polygon.points = std::move(points);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

double lebedev::getArea(const Polygon & polygon)
{
  double area = 0.0;
  std::vector< double > areas_pos(polygon.points.size());
  std::vector< double > areas_neg(polygon.points.size());
  std::vector< double > coords_x(polygon.points.size());
  std::vector< double > coords_y(polygon.points.size());
  std::transform(
    polygon.points.cbegin(),
    polygon.points.cend(),
    coords_x.begin(),
    getX
  );
  std::transform(
    polygon.points.cbegin(),
    polygon.points.cend(),
    coords_y.begin(),
    getY
  );

  std::copy(
    coords_x.cbegin(),
    --coords_x.cend(),
    areas_pos.begin()
  );
  areas_pos.shrink_to_fit();
  std::transform(
    areas_pos.begin(),
    areas_pos.end(),
    ++coords_y.cbegin(),
    areas_pos.begin(),
    std::multiplies< double >()
  );
  areas_pos.push_back((*(coords_x.cend()) * (*(coords_y.cbegin()))));

  std::copy(
    coords_y.cbegin(),
    --coords_y.cend(),
    areas_neg.begin()
  );
  areas_neg.shrink_to_fit();
  std::transform(
    areas_neg.begin(),
    areas_neg.end(),
    ++coords_x.cbegin(),
    areas_neg.begin(),
    std::multiplies< double >()
  );
  areas_neg.push_back((*(coords_y.cend()) * (*(coords_x.cbegin()))));

  area = std::accumulate(areas_pos.cbegin(), areas_pos.cend(), 0.0);
  area -= std::accumulate(areas_neg.cbegin(), areas_neg.cend(), 0.0);
  return 0.5 * std::abs(area);
}
