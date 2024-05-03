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
    std::map< std::string, std::function< bool(Polygon) > > areaOptions;
    {
      using namespace std::placeholders;
      areaOptions["EVEN"] = std::bind(std::equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
      areaOptions["ODD"] = std::bind(std::not_equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
      areaOptions["MEAN"] = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::bind(getSize, _1));
    }
    std::map< std::string, std::function< double(std::vector<Polygon>) > > areaStrategies;
    {
      using namespace std::placeholders;
      areaStrategies["EVEN"] = strategies::Sum;
      areaStrategies["ODD"] = strategies::Sum;
      areaStrategies["MEAN"] = strategies::Mean;
    }

    std::map< std::string, std::function< bool(Polygon, Polygon) > > findOptions;
    {
      using namespace std::placeholders;
      findOptions["VERTEXES"] = std::bind(std::less< size_t >{}, std::bind(getSize, _1), std::bind(getSize, _2));
      findOptions["AREA"] = std::bind(std::less< double >{}, std::bind(getArea, _1), std::bind(getArea, _2));
    }
    std::map< std::string, std::function< void(Polygon, std::ostream&) > > findStrategies;
    {
      using namespace std::placeholders;
      findStrategies["VERTEXES"] = strategies::Size;
      findStrategies["AREA"] = strategies::Area;
    }

    std::map< std::string, std::function< bool(Polygon) > > countOptions;
    {
      using namespace std::placeholders;
      countOptions["EVEN"] = std::bind(std::equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
      countOptions["ODD"] = std::bind(std::not_equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
    }

    using cmd = std::function< void(const std::vector< ibragimov::Polygon >&, std::istream&, std::ostream&) >;
    std::map< std::string, cmd > commands;
    {
      using namespace std::placeholders;
      commands["AREA"] = std::bind(ibragimov::calculateArea, areaOptions, areaStrategies, _1, _2, _3);
      commands["MAX"] = std::bind(ibragimov::findMax, findOptions, findStrategies, _1, _2, _3);
      commands["MIN"] = std::bind(ibragimov::findMin, findOptions, findStrategies, _1, _2, _3);
      commands["COUNT"] = std::bind(ibragimov::count, countOptions, _1, _2, _3);
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
