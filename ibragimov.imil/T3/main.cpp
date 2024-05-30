#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "FILE ERROR: file does not passed as argument\n";
    std::cerr << "INPUT FORMAT: lab <FILENAME>\n";
    return 1;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs.is_open())
  {
    std::cerr << "FILE INPUT ERROR: file does not exist\n";
    return 1;
  }
  std::vector< ibragimov::Polygon > polygons = {};
  while (!ifs.eof())
  {
    using is_iter = std::istream_iterator< ibragimov::Polygon >;
    std::copy(is_iter{ifs}, is_iter{}, std::back_inserter(polygons));
    ifs.clear();
    ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  ifs.close();

  {
    using namespace ibragimov;
    std::map< std::string, std::function< bool(const Polygon&) > > predicates;
    {
      using namespace std::placeholders;
      auto isEqual = std::bind(std::equal_to< size_t >{}, _1, _2);
      predicates["EVEN"] = std::bind(isEqual, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
      predicates["ODD"] = std::bind(std::logical_not< size_t >{}, std::bind(predicates["EVEN"], _1));
    }
    std::map< std::string, std::function< bool(const Polygon&, const Polygon&) > > comparators;
    {
      using namespace std::placeholders;
      comparators["VERTEXES"] = std::bind(std::less< size_t >{}, std::bind(getSize, _1), std::bind(getSize, _2));
      comparators["AREA"] = std::bind(std::less< double >{}, std::bind(calculateArea, _1), std::bind(calculateArea, _2));
    }

    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > areaOptions;
    {
      using namespace std::placeholders;
      areaOptions["EVEN"] = std::bind(outputDouble, _2, std::bind(accumAreaIf, _1, predicates["EVEN"]));
      areaOptions["ODD"] = std::bind(outputDouble, _2, std::bind(accumAreaIf, _1, predicates["ODD"]));
      areaOptions["MEAN"] = std::bind(outputDouble, _2, std::bind(accumMeanArea, _1));
    }
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > maxOptions;
    {
      using namespace std::placeholders;
      maxOptions["VERTEXES"] = std::bind(outputVertexes, _2, std::bind(findMax, _1, comparators["VERTEXES"]));
      maxOptions["AREA"] = std::bind(outputArea, _2, std::bind(findMax, _1, comparators["AREA"]));
    }
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > minOptions;
    {
      using namespace std::placeholders;
      minOptions["VERTEXES"] = std::bind(outputVertexes, _2, std::bind(findMin, _1, comparators["VERTEXES"]));
      minOptions["AREA"] = std::bind(outputArea, _2, std::bind(findMin, _1, comparators["AREA"]));
    }
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > countOptions;
    {
      using namespace std::placeholders;
      countOptions["EVEN"] = std::bind(outputULL, _2, std::bind(countIf, _1, predicates["EVEN"]));
      countOptions["ODD"] = std::bind(outputULL, _2, std::bind(countIf, _1, predicates["ODD"]));
    }

    using cmd = std::function< void(const std::vector< Polygon >&, std::istream&, std::ostream&) >;
    std::map< std::string, cmd > commands;
    {
      using namespace std::placeholders;
      commands["AREA"] = std::bind(getArea, areaOptions, _1, _2, _3);
      commands["MAX"] = std::bind(find, maxOptions, _1, _2, _3);
      commands["MIN"] = std::bind(find, minOptions, _1, _2, _3);
      commands["COUNT"] = std::bind(count, countOptions, _1, _2, _3);
      commands["PERMS"] = std::bind(countPerms, _1, _2, _3);
      commands["RIGHTSHAPES"] = std::bind(countRightshapes, _1, _3);
    }
    std::string command = "";
    while (std::cin >> command)
    {
      try
      {
        commands.at(command)(polygons, std::cin, std::cout);
      }
      catch (const std::exception&)
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }

  return 0;
}
