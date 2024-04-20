#include "figures_struct.hpp"
#include <limits>
#include <istream>
#include <iostream>
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

}