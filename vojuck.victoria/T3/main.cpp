#include <iterator>
#include <limits>
#include <fstream>

#include "polygon.hpp"
#include "inguard.hpp"

int main(int argc, char **argv)
{
  using namespace vojuck;
  if (argc != 2)
  {
    std::cout << "<SOURCE FILE NOT FOUND>\n";
    return 1;
  }

  std::ifstream source(argv[1]);
  if (!source.is_open())
  {
    std::cout << "<CANNOT OPEN SOURCE FILE>\n";
    return 1;
  }

  std::vector< Polygon > polygons;
  using polygonIterator = std::istream_iterator< Polygon >;
  while (!source.eof())
  {
    std::copy(polygonIterator{source}, polygonIterator{}, std::back_inserter(polygons));
    if (source.fail())
    {
      source.clear();
      source.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::ios_base::fmtflags f(std::cout.flags());
  std::cout << std::fixed << std::setprecision(1);

  while (!std::cin.eof())
  {
    std::string command = "";
    std::string heading = "";
    std::cin >> command;
    if (command == "AREA")
    {
      std::cin >> heading;
      calculateArea(polygons, heading);
    }
    if (command == "MAX" || command == "MIN")
    {
      std::cin >> heading;
      (command == "MAX" ? getMax(polygons, heading) : getMin(polygons, heading));
    }
    if (command == "COUNT")
    {
      std::cin >> heading;
      countPolygons(polygons, heading);
    }
    if (command == "RECTS")
    {
      Rects(polygons);
    }
  }
}
