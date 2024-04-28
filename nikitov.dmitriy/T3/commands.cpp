#include "commands.hpp"
#include <istream>
#include <vector>
#include <string>
#include "figures_struct.hpp"

bool isOdd(const nikitov::Polygon& figure)
{
  return figure.points.size() % 2;
}

void nikitov::area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;
}
