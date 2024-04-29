#include "CommandFacade.hpp"
#include <vector>
#include <limits>
#include "CommandFunctors.hpp"

sazanov::CommandFacade::CommandFacade(const std::vector< Polygon >& polygons) :
  polygons_(polygons)
{
  using namespace std::placeholders;
  commands_["AREA"] = std::bind(GetTotalPolygonsArea{getAreaSubCommands(), getEmptyVectorSupportInfo(), AccumulateAreaWithNumOfVertexes{}},
    polygons_, _1, _2);
  commands_["MAX"] = std::bind(GetMaxValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["MIN"] = std::bind(GetMinValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["COUNT"] = std::bind(CountPolygons{getCountSubcommands(), CountWithNumOfVertexes{}}, polygons_, _1, _2);
  commands_["MAXSEQ"] = std::bind(GetMaxSequence{}, polygons_, _1, _2);
  commands_["SAME"] = std::bind(CountSamePolygons{}, polygons_, _1, _2);
}

std::unordered_map<std::string, bool> sazanov::CommandFacade::getEmptyVectorSupportInfo()
{
  std::unordered_map< std::string, bool > emptyVectorSupport;
  emptyVectorSupport["ODD"] = true;
  emptyVectorSupport["EVEN"] = true;
  emptyVectorSupport["MEAN"] = false;
  return emptyVectorSupport;
}

sazanov::CommandFacade::AreaSubCommands sazanov::CommandFacade::getAreaSubCommands()
{
  AreaSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["ODD"] = std::bind(AccumulateArea{}, _1, _2, true);
  subCommands["EVEN"] = std::bind(AccumulateArea{}, _1, _2, false);
  subCommands["MEAN"] = std::bind(AccumulateMeanArea{polygons_.size()}, _1, _2);
  return subCommands;
}

sazanov::CommandFacade::MaxMinSubCommands sazanov::CommandFacade::getMaxMinSubCommands()
{
  MaxMinSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["AREA"] = std::pair<Comparator, OutputValueFunctor>(AreaComparator{}, OutputArea{});
  subCommands["VERTEXES"] = std::pair<Comparator, OutputValueFunctor>(VertexComparator{}, OutputVertex{});
  return subCommands;
}

sazanov::CommandFacade::CountSubCommands sazanov::CommandFacade::getCountSubcommands()
{
  CountSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["ODD"] = std::bind(CountWithParity{}, _1, true);
  subCommands["EVEN"] = std::bind(CountWithParity{}, _1, false);
  return subCommands;
}

void sazanov::CommandFacade::nextCommand(std::istream& in, std::ostream& out)
{
  std::string commandKey;
  in >> commandKey;
  if (in)
  {
    try
    {
      CommandFunctor& command = commands_.at(commandKey);
      command(in, out);
    }
    catch (const std::exception&)
    {
      out << "<INVALID COMMAND>";
    }
  }
}
