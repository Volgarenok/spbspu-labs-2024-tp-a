#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <fstream>
#include <algorithm>
#include "Polygon.hpp"
#include "Commands.hpp"
#include "CommandPredicates.hpp"

using namespace sazanov;
int main(int argc, char* argv[])
{
 if (argc < 2)
  {
    std::cerr << "missed filename argument\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cant open file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it_t{file}, input_it_t{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  using AccumulatePredicate = std::function< double(double, const Polygon&) >;
  using AreaSubCommands = std::unordered_map< std::string, AccumulatePredicate >;
  AreaSubCommands areaSubCommands;
  using namespace std::placeholders;
  areaSubCommands["ODD"] = std::bind(accumulateAreaWithParity, _1, _2, true);
  areaSubCommands["EVEN"] = std::bind(accumulateAreaWithParity, _1, _2, false);
  areaSubCommands["MEAN"] = std::bind(accumulateMeanArea, _1, _2, polygons.size());

  std::unordered_map< std::string, bool > emptyVectorSupport;
  emptyVectorSupport["ODD"] = true;
  emptyVectorSupport["EVEN"] = true;
  emptyVectorSupport["MEAN"] = false;

  using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
  using OutputValuePredicate = std::function< void(const Polygon&, std::ostream& out) >;
  using MaxMinSubCommands = std::unordered_map< std::string, std::pair< Comparator, OutputValuePredicate > >;
  MaxMinSubCommands maxMinSubCommands;
  maxMinSubCommands["AREA"] = std::pair<Comparator, OutputValuePredicate>(compareArea, outputArea);
  maxMinSubCommands["VERTEXES"] = std::pair<Comparator, OutputValuePredicate>(compareVertex, outputVertex);

  using CountPredicate = std::function< bool(const Polygon&) >;
  using CountSubCommands = std::unordered_map< std::string, CountPredicate >;
  CountSubCommands countSubCommands;
  countSubCommands["ODD"] = std::bind(countWithParity, _1, true);
  countSubCommands["EVEN"] = std::bind(countWithParity, _1, false);

  using CommandFunctor = std::function< void(std::istream& in, std::ostream& out) >;
  std::unordered_map< std::string, CommandFunctor > commands;

  commands["AREA"] = std::bind(GetTotalPolygonsArea{areaSubCommands, emptyVectorSupport, accumulateAreaWithNumOfVertexes},
    polygons, _1, _2);
  commands["MAX"] = std::bind(GetMaxValue{maxMinSubCommands}, polygons, _1, _2);
  commands["MIN"] = std::bind(GetMinValue{maxMinSubCommands}, polygons, _1, _2);
  commands["COUNT"] = std::bind(CountPolygons{countSubCommands, countWithNumOfVertexes}, polygons, _1, _2);
  commands["MAXSEQ"] = std::bind(getMaxSequence, polygons, _1, _2);
  commands["SAME"] = std::bind(countSamePolygons, polygons, _1, _2);

  std::string commandKey;
  std::cin >> commandKey;
  while (!std::cin.eof())
  {
    try
    {
      const CommandFunctor& command = commands.at(commandKey);
      command(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cout << '\n';
    std::cin >> commandKey;
  }
  return 0;
}
