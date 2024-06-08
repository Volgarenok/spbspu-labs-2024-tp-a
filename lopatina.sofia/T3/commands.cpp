#include "commands.hpp"
#include <iomanip>
#include <algorithm>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include "implementation_cmds.hpp"
#include "stream_guard.hpp"

void lopatina::areaCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds;
  cmds["EVEN"] = std::bind(areaEven, figures);
  cmds["ODD"] = std::bind(areaOdd, figures);
  cmds["MEAN"] = std::bind(areaMean, figures);
  std::string cmd;
  in >> cmd;
  if ((cmd == "MEAN") && figures.empty())
  {
    throw std::logic_error("No figure");
  }
  StreamGuard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  try
  {
    out << cmds.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    out << areaNum(figures, num) << '\n';
  }
}

void lopatina::maxCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds_area;
  std::map<std::string, std::function<size_t()>> cmds_vertexes;
  cmds_area["AREA"] = std::bind(maxArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(maxVertexes, figures);
  std::string cmd;
  in >> cmd;
  if (figures.empty())
  {
    throw std::logic_error("No figures");
  }
  try
  {
    out << cmds_vertexes.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    StreamGuard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << cmds_area.at(cmd)() << '\n';
  }
}

void lopatina::minCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds_area;
  std::map<std::string, std::function<size_t()>> cmds_vertexes;
  cmds_area["AREA"] = std::bind(minArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(minVertexes, figures);
  std::string cmd;
  in >> cmd;
  if (figures.empty())
  {
    throw std::logic_error("No figures");
  }
  try
  {
    out << cmds_vertexes.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    StreamGuard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << cmds_area.at(cmd)() << '\n';
  }
}

void lopatina::countCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<size_t()>> cmds;
  cmds["EVEN"] = std::bind(countEven, figures);
  cmds["ODD"] = std::bind(countOdd, figures);
  std::string cmd;
  in >> cmd;
  try
  {
    out << cmds.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    out << countNum(figures, num) << '\n';
  }
}
