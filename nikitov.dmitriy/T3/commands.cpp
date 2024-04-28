#include "commands.hpp"
#include <istream>
#include <algorithm>
#include <vector>
#include <string>
#include <figures_struct.hpp>

bool isOdd(const nikitov::Polygon& figure)
{
  return figure.points.size() % 2;
}

double countArea(nikitov::Point first, nikitov::Point second, nikitov::Point third)
{
  return 0.5 * ((first.x - third.x) * (second.y - third.y) - (second.x - third.x) * (first.y - third.y));
}

void nikitov::area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;
  if (parameter == "ODD")
  {
    std::find_if(data.cbegin(), data.cend(), isOdd);
  }
  else if (parameter == "EVEN")
  {
    std::find_if(data.cbegin(), data.cend(), !isOdd);
  }
}
