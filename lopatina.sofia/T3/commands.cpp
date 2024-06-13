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
  cmds["EVEN"] = std::bind(doAreaEven, figures);
  cmds["ODD"] = std::bind(doAreaOdd, figures);
  cmds["MEAN"] = std::bind(doAreaMean, figures);
  std::string cmd;
  in >> cmd;
  if ((cmd == "MEAN") && figures.empty())
  {
    throw std::logic_error("No figures");
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
    if (num < 3)
    {
      throw std::logic_error("Not figure");
    }
    out << doAreaNum(figures, num) << '\n';
  }
}

void lopatina::maxCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function<double()>> cmds_area;
  std::map<std::string, std::function<size_t()>> cmds_vertexes;
  cmds_area["AREA"] = std::bind(doMaxArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(doMaxVertexes, figures);
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
  cmds_area["AREA"] = std::bind(doMinArea, figures);
  cmds_vertexes["VERTEXES"] = std::bind(doMinVertexes, figures);
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
  cmds["EVEN"] = std::bind(doCountEven, figures);
  cmds["ODD"] = std::bind(doCountOdd, figures);
  std::string cmd;
  in >> cmd;
  try
  {
    out << cmds.at(cmd)() << '\n';
  }
  catch (const std::out_of_range &)
  {
    size_t num = std::stoull(cmd);
    if (num < 3)
    {
      throw std::logic_error("Not figure");
    }
    out << doCountNum(figures, num) << '\n';
  }
}

void lopatina::maxSeqCmd(const std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  Polygon given_figure;
  in >> given_figure;
  if (!in)
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::logic_error("Invalid given figure");
  }
  out << doMaxSeq(figures, given_figure) << '\n';
}

void lopatina::rmEchoCmd(std::vector<Polygon> & figures, std::istream & in, std::ostream & out)
{
  Polygon given_figure;
  in >> given_figure;
  if (!in)
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::logic_error("Invalid given figure");
  }
  out << doRmEcho(figures, given_figure) << '\n';
}

void lopatina::rightShapesCmd(const std::vector<Polygon> & figures, std::ostream & out)
{
  out << doRightShapes(figures) << '\n';
}
