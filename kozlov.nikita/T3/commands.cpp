#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include <numeric>
#include <climits>
#include <streamGuard.hpp>
#include "figures_operations.hpp"

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
  out << std::fixed << std::setprecision(1);
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
  cmdsVert["VERTEXES"] = std::bind(getMaxVertexes, poly);

  StreamGuard guard(out);
  if (cmdsArea.find(subcommand) != cmdsArea.end())
  {
    out << std::fixed << std::setprecision(1);
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
  cmdsVert["VERTEXES"] = std::bind(getMinVertexes, poly);

  StreamGuard guard(out);
  if (cmdsArea.find(subcommand) != cmdsArea.end())
  {
    out << std::fixed << std::setprecision(1);
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

void kozlov::doCmdCount(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  size_t result = 0;
  std::string subcommand;
  in >> subcommand;

  std::map< std::string, std::function< size_t() > > cmds;
  using namespace std::placeholders;
  cmds["EVEN"] = std::bind(countEvenPoly, poly);
  cmds["ODD"] = std::bind(countOddPoly, poly);

  size_t vertexNum = 0;
  try
  {
    vertexNum = std::stoull(subcommand);
    if (vertexNum < 3)
    {
      throw std::logic_error("<INCORRECT VERTEX NUMBER>");
    }
    result = countNumPoly(poly, vertexNum);
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
  out << result << '\n';
}

void kozlov::doCmdEcho(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  Polygon target;
  in >> target;
  if (!in)
  {
    throw std::logic_error("<WRONG TARGET POLYGON>");
  }
  size_t count = std::count(poly.begin(), poly.end(), target);
  if (count == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  echoPolygons(poly, target);
  out << count << '\n';
}

void kozlov::doCmdInframe(std::vector< Polygon >& poly, std::istream& in, std::ostream& out)
{
  Polygon target;
  in >> target;
  if (!in)
  {
    throw std::logic_error("<WRONG TARGET POLYGON>");
  }
  std::set< Point > uniquePoints(target.points.begin(), target.points.end());
  if (uniquePoints.size() != target.points.size())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::pair< Point, Point > initialFrame = {{0, 0}, {0, 0}};
  std::pair< Point, Point > frame = std::accumulate(poly.begin(), poly.end(), initialFrame, calcFrame);
  auto isPointInFrame = std::bind(checkPointInFrame, frame, std::placeholders::_1);
  bool isPointsInside = std::all_of(target.points.begin(), target.points.end(), isPointInFrame);
  out << (isPointsInside ? "<TRUE>" : "<FALSE>") << '\n';
}
