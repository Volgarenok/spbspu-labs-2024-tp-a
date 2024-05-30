#include "commands.hpp"
#include <string>
#include <stdexcept>
#include <interface.hpp>
#include "<delimiter.hpp>

chernikova::Commands chernikova::initializeCommands()
{
  Commands commandsSet;

  commandsSet.insert({ "AREA", getArea });
  commandsSet.insert({ "MAX", getMax });
  commandsSet.insert({ "MIN", getMin });
  commandsSet.insert({ "COUNT", getCount });
  commandsSet.insert({ "ECHO", echoDuplicate });
  commandsSet.insert({ "INTERSECTIONS", getIntersections });
  commandsSet.insert({ "RIGHTSHAPES", getRightShapes });

  return commandsSet;
}

bool chernikova::doCommand(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  StreamGuard streamGuard(in);
  in.unsetf(std::ios_base::skipws);

  static Commands functions = initializeCommands();

  std::string command;
  in >> command;

  if (in.eof())
  {
    return false;
  }

  if (!in)
  {
    handleError(in, out);
    return true;
  }

  try
  {
    functions.at(command)(polygons, out, in);
  }
  catch (const std::out_of_range& error)
  {
    handleError(in, out);
    return true;
  }

  return true;
}

void chernikova::getArea(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  if (subcommand == "EVEN")
  {
    getAreaEven(polygons, out);
  }
  else if (subcommand == "ODD")
  {
    getAreaOdd(polygons, out);
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      printError(out);
      return;
    }

    getAreaMean(polygons, out);
  }
  else
  {
    size_t count = 0;

    try
    {
      size_t numberOfSymbols;
      count = std::stoll(subcommand, &numberOfSymbols);
    }
    catch (const std::exception& error)
    {
      printError(out);
      return;
    }

    if (count < 3)
    {
      printError(out);
      return;
    }
    getAreaVertexes(polygons, count, out);
  }
}

void chernikova::getMax(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  if (polygons.empty())
  {
    printError(out);
    return;
  }

  if (subcommand == "AREA")
  {
    getMaxArea(polygons, out);
  }
  else if (subcommand == "VERTEXES")
  {
    getMaxVertexes(polygons, out);
  }
  else
  {
    printError(out);
    return;
  }
}

void chernikova::getMin(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  if (polygons.empty())
  {
    printError(out);
    return;
  }

  if (subcommand == "AREA")
  {
    getMinArea(polygons, out);
  }
  else if (subcommand == "VERTEXES")
  {
    getMinVertexes(polygons, out);
  }
  else
  {
    printError(out);
    return;
  }
}

void chernikova::getCount(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  std::string subcommand;
  in >> ExactSymbolI{ ' ' } >> subcommand >> ExactSymbolI{ '\n' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  if (subcommand == "EVEN")
  {
    getCountEven(polygons, out);
  }
  else if (subcommand == "ODD")
  {
    getCountOdd(polygons, out);
  }
  else
  {
    size_t count = 0;

    try
    {
      size_t numberOfSymbols;
      count = std::stoll(subcommand, &numberOfSymbols);
    }
    catch (const std::exception& error)
    {
      printError(out);
      return;
    }

    if (count < 3)
    {
      printError(out);
      return;
    }

    getCountVertexes(polygons, count, out);
  }
}

void chernikova::echoDuplicate(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  Polygon polygon;
  in >> ExactSymbolI{ ' ' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  in >> polygon;

  if (!in)
  {
    printError(out);
    in.clear();
    return;
  }

  if (!in)
  {
    handleError(in, out);
    return;
  }

  echo(polygons, polygon, out);
}

void chernikova::getIntersections(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  Polygon polygon;
  in >> ExactSymbolI{ ' ' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  in >> polygon;

  if (!in)
  {
    printError(out);
    in.clear();
    return;
  }

  if (!in)
  {
    handleError(in, out);
    return;
  }

  if (polygons.empty())
  {
    printError(out);
    return;
  }

  intersections(polygons, polygon, out);
}

void chernikova::getRightShapes(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in)
{
  in >> ExactSymbolI{ '\n' };

  if (!in)
  {
    handleError(in, out);
    return;
  }

  if (polygons.empty())
  {
    printError(out);
    return;
  }

  rightShapes(polygons, out);
}
