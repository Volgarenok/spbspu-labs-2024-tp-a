#include <fstream>
#include <limits>
#include <map>
#include <functional>
#include <iomanip>
#include <iterator>
#include "commands.h"
#include "Polygon.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong parameters\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "Error reading file\n";
    return 2;
  }
  using namespace kartamyshev;
  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!in.eof())
  {
    std::copy(input_it_t{ in }, input_it_t{}, std::back_inserter(polygons));
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
    commands["SAME"] = std::bind(same, std::cref(polygons), _1, _2);
    commands["RECTS"] = std::bind(rects, std::cref(polygons), _2);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
