#include "commands.hpp"
#include <functional>
#include <map>
#include <iomanip>
#include <streamGuard.hpp>
#include "utils.hpp"

void kozlov::doCmdArea(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string subcommand;
  in >> subcommand;

  std::map< std::string, std::function< double() > > cmds;
  using namespace std::placeholders;
  cmds["EVEN"] = std::bind(calcEvenArea, poly);
  cmds["ODD"] = std::bind(calcOddArea, poly);
  cmds["MEAN"] = std::bind(calcMeanArea, poly);

  size_t vertexNum = 0;
  try
  {
    vertexNum = std::stoull(subcommand);
    if (vertexNum < 3)
    {
      throw std::logic_error("<INCORRECT VERTEX NUMBER>");
    }
    result = calcNumVertexArea(poly, vertexNum);
  }
  catch (const std::invalid_argument&)
  {
    if (cmds.find(subcommand) != cmds.end())
    {
      result = cmds[subcommand]();
    }
    else
    {
      throw std::invalid_argument("<INVALID SUBARGUMENT>");
    }
  }
  StreamGuard guard(out);
  out << std::setprecision(1);
  out << result << '\n';
}

void kozlov::doCmdMax(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  std::string subcommand;
  in >> subcommand;

  using namespace std::placeholders;
  std::map< std::string, std::function< double() > > cmdsArea;
  cmdsArea["AREA"] = std::bind(getMaxArea, poly);

  std::map< std::string, std::function< double() > > cmdsVert;
  cmdsArea["VERTEXES"] = std::bind(getMaxVertexes, poly);

  StreamGuard guard(out);
  out << std::setprecision(1);
  if (cmdsArea.find(subcommand) != cmdsArea.end())
  {
    out << std::setprecision(1);
    out << cmdsArea[subcommand]() << '\n';
  }
  else if (cmdsVert.find(subcommand) != cmdsVert.end())
  {
    out << cmdsVert[subcommand]() << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID SUBARGUMENT>");
  }
}

void kozlov::doCmdMin(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  std::string subcommand;
  in >> subcommand;

  using namespace std::placeholders;
  std::map< std::string, std::function< double() > > cmdsArea;
  cmdsArea["AREA"] = std::bind(getMinArea, poly);

  std::map< std::string, std::function< double() > > cmdsVert;
  cmdsArea["VERTEXES"] = std::bind(getMinVertexes, poly);

  StreamGuard guard(out);
  if (cmdsArea.find(subcommand) != cmdsArea.end())
  {
    out << std::setprecision(1);
    out << cmdsArea[subcommand]() << '\n';
  }
  else if (cmdsVert.find(subcommand) != cmdsVert.end())
  {
    out << cmdsVert[subcommand]() << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID SUBARGUMENT>");
  }
}
