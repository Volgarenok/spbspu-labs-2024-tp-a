#include "CommandFacade.hpp"
#include <vector>
#include <algorithm>
#include <limits>
#include "CommandFunctors.hpp"

sazanov::CommandFacade::CommandFacade(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out) :
  polygons_(polygons),
  in_(in),
  out_(out)
{
  using namespace std::placeholders;
  commands_["AREA"] = std::bind(GetTotalPolygonsArea{getAreaSubCommands(), AccumulateAreaWithNumOfVertexes{}}, polygons_, _1, _2);
  commands_["MAX"] = std::bind(GetMaxValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["MIN"] = std::bind(GetMinValue{getMaxMinSubCommands()}, polygons_, _1, _2);
  commands_["COUNT"] = std::bind(CountPolygons{getCountSubcommands(), CountWithNumOfVertexes{}}, polygons_, _1, _2);
  commands_["MAXSEQ"] = std::bind(GetMaxSequence{}, polygons_, _1, _2);
  commands_["SAME"] = std::bind(CountSamePolygons{}, polygons_, _1, _2);

  subCommandKeyInput_["AREA"] = std::pair<GetSubCommandKeyFunctor, bool>(ReadOneWordKey{}, true);
  subCommandKeyInput_["MAX"] = subCommandKeyInput_["AREA"];
  subCommandKeyInput_["MIN"] = subCommandKeyInput_["AREA"];
  subCommandKeyInput_["COUNT"] = subCommandKeyInput_["AREA"];
  subCommandKeyInput_["MAXSEQ"] = std::pair<GetSubCommandKeyFunctor, bool>(ReadPolygonKey{}, false);
  subCommandKeyInput_["SAME"] = std::pair<GetSubCommandKeyFunctor, bool>(ReadPolygonKey{}, false);
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

void sazanov::CommandFacade::nextCommand()
{
  std::string commandKey;
  in_ >> commandKey;
  bool isIgnoreRequired = true;
  if (in_)
  {
    try
    {
      CommandFunctor& command = commands_.at(commandKey);
      std::string subCommandKey;
      auto subCommandKeyInputFunctor = subCommandKeyInput_.at(commandKey).first;
      isIgnoreRequired = subCommandKeyInput_.at(commandKey).second;
      subCommandKeyInputFunctor(subCommandKey, in_);
      command(subCommandKey, out_);
    }
    catch (const std::exception&)
    {
      out_ << "<INVALID COMMAND>";
    }
  }
  in_.clear();
  if (isIgnoreRequired)
  {
    in_.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
