#include "Polygon.hpp"
#include "Commands.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include <numeric>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
     std::cout << "Required filename argument\n";
     return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "File cannot be opened\n";
    return 2;
  }

  using namespace erfurt;
  using namespace std::placeholders;

  if (!file.is_open())
  {
    throw std::invalid_argument("File is not open\n");
  }

  std::vector<Polygon> polygons;
  using input_it_it = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_it{file}, input_it_it{}, std::back_inserter(polygons));
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map<std::string, std::function<void(std::istream &, std::ostream &)>> commands;
  commands["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
  commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
  commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
  commands["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
  commands["PERMS"] = std::bind(perm, std::cref(polygons), _1, _2);
  commands["RMECHO"] = std::bind(rmecho, std::ref(polygons), _1, _2);;

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
