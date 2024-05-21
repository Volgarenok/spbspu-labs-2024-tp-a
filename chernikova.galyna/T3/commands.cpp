#include "commands.hpp"

#include <Delimiter.hpp>

std::string chernikova::inputCommand(std::istream& in)
{
  std::string command;
  getline(in, command);
  if (!in)
  {
    throw std::runtime_error("Error input");
  }

  return command;
}

void chernikova::Commands::doCommand(const std::vector< Polygon >& polygons, const std::string& cmd, std::ostream& out) const
{
  auto func = dict1_.at(cmd);
  func(polygons, out);
}

void chernikova::Commands::doCommand(std::vector< Polygon >& polygons, const Commands& dict, const std::string& cmd, std::ostream& out, std::istream& in)
{
  std::cout << "com = " << cmd << '\n';
  std::istringstream iss ( (std::string(cmd)) );
  std::string cmd_str;
  iss >> cmd_str;

  auto it1 = dict1_.find(cmd);

  if(it1 != dict1_.end())
  {
    dict.doCommand(polygons, cmd, out);
    return;
  }

  auto it2 = dict2_.find(cmd_str);

  if(it2 != dict2_.end())
  {
    size_t num;
    iss >> num;
    if (!in)
    {
      throw std::invalid_argument("Error input");
    }
    dict.doCommand(polygons, cmd_str, num, out);
    return;
  }

  auto it3 = dict3_.find(cmd_str);

  if (it3 != dict3_.end())
  {
    Polygon polygon;
    iss >> polygon >> DelimiterI{ '\n' };
    if (!in)
    {
      throw std::invalid_argument("Error input");
    }
    dict.doCommand(polygons, cmd_str, polygon, out);
    return;
  }
}
