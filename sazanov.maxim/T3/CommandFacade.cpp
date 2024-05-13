#include "CommandFacade.hpp"
#include <vector>
#include "Commands.hpp"
#include "CommandPredicates.hpp"

sazanov::CommandFacade::CommandFacade(const std::vector< Polygon >& polygons) :
  polygons_(polygons)
{
  using namespace std::placeholders;
  commands_["AREA"] = std::bind(GetTotalPolygonsArea{getAreaSubCommands(), getEmptyVectorSupportInfo(), accumulateAreaWithNumOfVertexes},
    polygons_, _1, _2);
  commands_["MAX"] = std::bind(GetMaxValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["MIN"] = std::bind(GetMinValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["COUNT"] = std::bind(CountPolygons{getCountSubcommands(), countWithNumOfVertexes}, polygons_, _1, _2);
  commands_["MAXSEQ"] = std::bind(getMaxSequence, polygons_, _1, _2);
  commands_["SAME"] = std::bind(countSamePolygons, polygons_, _1, _2);
}

std::unordered_map<std::string, bool> sazanov::CommandFacade::getEmptyVectorSupportInfo() const
{
  std::unordered_map< std::string, bool > emptyVectorSupport;
  emptyVectorSupport["ODD"] = true;
  emptyVectorSupport["EVEN"] = true;
  emptyVectorSupport["MEAN"] = false;
  return emptyVectorSupport;
}

sazanov::CommandFacade::AreaSubCommands sazanov::CommandFacade::getAreaSubCommands() const
{
  AreaSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["ODD"] = std::bind(accumulateAreaWithParity, _1, _2, true);
  subCommands["EVEN"] = std::bind(accumulateAreaWithParity, _1, _2, false);
  subCommands["MEAN"] = std::bind(accumulateMeanArea, _1, _2, polygons_.size());
  return subCommands;
}

sazanov::CommandFacade::MaxMinSubCommands sazanov::CommandFacade::getMaxMinSubCommands() const
{
  MaxMinSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["AREA"] = std::pair<Comparator, OutputValuePredicate>(compareArea, outputArea);
  subCommands["VERTEXES"] = std::pair<Comparator, OutputValuePredicate>(compareVertex, outputVertex);
  return subCommands;
}

sazanov::CommandFacade::CountSubCommands sazanov::CommandFacade::getCountSubcommands() const
{
  CountSubCommands subCommands;
  using namespace std::placeholders;
  subCommands["ODD"] = std::bind(countWithParity, _1, true);
  subCommands["EVEN"] = std::bind(countWithParity, _1, false);
  return subCommands;
}

void sazanov::CommandFacade::nextCommand(std::istream& in, std::ostream& out) const
{
  std::string commandKey;
  in >> commandKey;
  if (in)
  {
    try
    {
      const CommandFunctor& command = commands_.at(commandKey);
      command(in, out);
    }
    catch (const std::exception&)
    {
      out << "<INVALID COMMAND>";
    }
  }
}
