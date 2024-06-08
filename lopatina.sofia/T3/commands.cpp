#include "commands.hpp"
#include <algorithm>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include "implementation_cmds.hpp"

void lopatina::areaCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  out << "AREA\n";
  using namespace std::placeholders;
  std::map<std::string, std::function<void()>> cmds;
  cmds["EVEN"] = std::bind(areaEven, figures);
  cmds["ODD"] = std::bind(areaOdd, figures);
  cmds["MEAN"] = std::bind(areaMean, figures);
  std::string cmd;
  in >> cmd;
  if ((cmd == "MEAN") && figures.empty())
  {
    throw std::logic_error("No figure");
  }
  try
  {
    cmds.at(cmd)();
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    areaNum(figures, num);
  }
}

void lopatina::maxCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  out << "MAX\n";
  using namespace std::placeholders;
  std::map<std::string, std::function<void()>> cmds;
  cmds["AREA"] = std::bind(maxArea, figures);
  cmds["VERTEXES"] = std::bind(maxVertexes, figures);
  std::string cmd;
  in >> cmd;
  if (figures.empty())
  {
    throw std::logic_error("No figures");
  }
  cmds.at(cmd)();
}

void lopatina::minCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  out << "MIN\n";
  using namespace std::placeholders;
  std::map<std::string, std::function<void()>> cmds;
  cmds["AREA"] = std::bind(minArea, figures);
  cmds["VERTEXES"] = std::bind(minVertexes, figures);
  std::string cmd;
  in >> cmd;
  if (figures.empty())
  {
    throw std::logic_error("No figures");
  }
  cmds.at(cmd)();
}

void lopatina::countCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  out << "COUNT\n";
  using namespace std::placeholders;
  std::map<std::string, std::function<void()>> cmds;
  cmds["EVEN"] = std::bind(countEven, figures);
  cmds["ODD"] = std::bind(countOdd, figures);
  std::string cmd;
  in >> cmd;
  try
  {
    cmds.at(cmd)();
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    countNum(figures, num);
  }
}
