#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <functional>
#include <iomanip>
#include <map>

#include "geometry.hpp"
#include "inputShapes.hpp"
#include "commands.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    return 1;
  }

  std::vector < zhalilov::Polygon > polygons;
  while (!file.eof())
  {
    std::copy(
        std::istream_iterator < zhalilov::Polygon >(file),
        std::istream_iterator < zhalilov::Polygon >(),
        std::back_inserter(polygons)
        );
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
    }
  }

  using cmdMaster = std::map < std::string, std::function < void(std::istream &, std::ostream &) > >;
  using namespace std::placeholders;
  cmdMaster master;
  master["AREA"] = std::bind(zhalilov::commands::area, std::cref(polygons), _1, _2);
  master["MAX"] = std::bind(zhalilov::commands::max, std::cref(polygons), _1, _2);
  master["MIN"] = std::bind(zhalilov::commands::min, std::cref(polygons), _1, _2);
  master["COUNT"] = std::bind(zhalilov::commands::count, std::cref(polygons), _1, _2);
  master["MAXSEQ"] = std::bind(zhalilov::commands::maxSeq, std::cref(polygons), _1, _2);
  master["INFRAME"] = std::bind(zhalilov::commands::inFrame, std::cref(polygons), _1, _2);

  std::string command;
  std::cout << std::setprecision(1) << std::fixed;
  while (std::cin >> command)
  {
    if (std::cin.eof())
    {
      return 0;
    }
    try
    {
      master.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::invalid_argument &)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
  }
}
