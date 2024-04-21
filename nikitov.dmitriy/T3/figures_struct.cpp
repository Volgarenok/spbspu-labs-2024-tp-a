#include "figures_struct.hpp"
#include <limits>
#include <istream>
#include <iterator>
#include <algorithm>
#include <delimiter.hpp>

std::istream& nikitov::operator>>(std::istream& input, Point& value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  using DelChar = DelimiterChar;
  input >> DelChar({'('}) >> value.x >> DelChar({';'}) >> value.y >> DelChar({')'});

  return input;
}

std::istream& nikitov::operator>>(std::istream& input, Polygon& value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  size_t pointsNum = {};
  input >> pointsNum;

  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ input }, pointsNum, std::back_inserter(value.points));
  if (!input.eof())
  {
    if (input.fail())
    {
      value.points.clear();
      input.clear();
    }
  }
  input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

  return input;
}
