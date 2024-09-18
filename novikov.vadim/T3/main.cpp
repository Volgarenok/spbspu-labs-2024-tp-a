#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument provided!\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: can't open the file!\n";
    return 2;
  }

  using namespace novikov;
  std::vector< Polygon > polygons;

  while (!file.eof())
  {
    using input_it_t = std::istream_iterator< Polygon >;
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  cmd::area_args_t area_arguments;

  using namespace std::placeholders;
  area_arguments["EVEN"] = AreaCalculator{ std::bind(calculateAreaIf, _1, hasEvenVertexesCount), EmptyVectors::Enabled };
  area_arguments["ODD"] = AreaCalculator{ std::bind(calculateAreaIf, _1, hasOddVertexesCount), EmptyVectors::Enabled };
  area_arguments["MEAN"] = AreaCalculator{ std::bind(calculateMeanArea, _1, polygons.size()), EmptyVectors::Disabled };

  cmd::minmax_args_t max_arguments;

  max_arguments["AREA"] = std::bind(minmaxArea< Max >, _1, _2);
  max_arguments["VERTEXES"] = std::bind(minmaxVertexes< Max >, _1, _2);

  cmd::minmax_args_t min_arguments;

  min_arguments["AREA"] = std::bind(minmaxArea< Min >, _1, _2);
  min_arguments["VERTEXES"] = std::bind(minmaxVertexes< Min >, _1, _2);

  cmd::count_args_t count_arguments;

  count_arguments["EVEN"] = hasEvenVertexesCount;
  count_arguments["ODD"] = hasOddVertexesCount;

  std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

  commands["AREA"] = std::bind(cmd::area, std::cref(area_arguments), std::cref(polygons), _1, _2);
  commands["MAX"] = std::bind(cmd::minmax, std::cref(max_arguments), std::cref(polygons), _1, _2);
  commands["MIN"] = std::bind(cmd::minmax, std::cref(min_arguments), std::cref(polygons), _1, _2);
  commands["COUNT"] = std::bind(cmd::count, std::cref(count_arguments), std::cref(polygons), _1, _2);
  commands["ECHO"] = std::bind(cmd::echo, std::ref(polygons), _1, _2);
  commands["INFRAME"] = std::bind(cmd::inFrame, std::cref(polygons), _1, _2);

  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  file.close();

  return 0;
}
