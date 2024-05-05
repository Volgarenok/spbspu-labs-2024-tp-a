#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include "commands.hpp"
#include "polygon.hpp"

int main()
{
  std::vector< ibragimov::Polygon > polygons = {};

  std::ifstream ifs("input.txt");
  if (ifs.is_open())
  {
    using is_iter = std::istream_iterator< ibragimov::Polygon >;
    std::copy(is_iter{ifs}, is_iter{}, std::back_inserter(polygons));
    if (!ifs)
    {
      ifs.clear();
      ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    ifs.close();
  }

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
      comparators["AREA"] = std::bind(std::less< double >{}, std::bind(getArea, _1), std::bind(getArea, _2));
    }

    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > areaOptions;
    {
      using namespace std::placeholders;
      areaOptions["EVEN"] = std::bind(strategies::SumIf, _1, predicates["EVEN"], _2);
      areaOptions["ODD"] = std::bind(strategies::SumIf, _1, predicates["ODD"], _2);
      areaOptions["MEAN"] = std::bind(strategies::Mean, _1, _2);
    }
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > maxOptions;
    {
      using namespace std::placeholders;
      maxOptions["VERTEXES"] = std::bind(strategies::Vertexes, std::bind(strategies::Max, _1, comparators["VERTEXES"]), _2);
      maxOptions["AREA"] = std::bind(strategies::Area, std::bind(strategies::Max, _1, comparators["AREA"]), _2);
    }
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > minOptions;
    {
      using namespace std::placeholders;
      minOptions["VERTEXES"] = std::bind(strategies::Vertexes, std::bind(strategies::Min, _1, comparators["VERTEXES"]), _2);
      minOptions["AREA"] = std::bind(strategies::Area, std::bind(strategies::Min, _1, comparators["AREA"]), _2);
    }

    using cmd = std::function< void(const std::vector< ibragimov::Polygon >&, std::istream&, std::ostream&) >;
    std::map< std::string, cmd > commands;
    {
      using namespace std::placeholders;
      commands["AREA"] = std::bind(ibragimov::calculateArea, areaOptions, _1, _2, _3);
      commands["MAX"] = std::bind(ibragimov::find, maxOptions, _1, _2, _3);
      commands["MIN"] = std::bind(ibragimov::find, minOptions, _1, _2, _3);
      commands["COUNT"] = std::bind(ibragimov::count, predicates, _1, _2, _3);
      commands["PERMS"] = std::bind(ibragimov::perms, _1, _2, _3);
    }
    std::string command = "";
    while (std::cin >> command)
    {
      try
      {
        commands.at(command)(polygons, std::cin, std::cout);
      }
      catch (...)
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
    }
  }

  return 0;
}
