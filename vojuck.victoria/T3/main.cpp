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
    std::cerr << "<SOURCE FILE NOT FOUND>\n";
    return 1;
  }

  std::ifstream source(argv[1]);
  if (!source.is_open())
  {
    std::cerr << "<CANNOT OPEN SOURCE FILE>\n";
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
    else if (command == "MAX" || command == "MIN")
    {
      std::cin >> heading;
      (command == "MAX" ? getMax(polygons, heading) : getMin(polygons, heading));
    }
    else if (command == "COUNT")
    {
      std::cin >> heading;
      countPolygons(polygons, heading);
    }
    else if (command == "RECTS")
    {
      rects(polygons);
    }
    else if (command == "MAXSEQ")
    {
      maxSeq(polygons, std::cin);
    }
    else if (command ==  "INTERSECTIONS")
    {
      intersections(polygons, std::cin);
    }
    else
    {
      if (!std::cin.eof())
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
}
