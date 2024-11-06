#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include <map>
#include "polygon.hpp"

namespace chernikova
{
  using Command = void (*)(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  using Commands = std::map< std::string, Command >;

  Commands initializeCommands();
  void doCommand(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  void getArea(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);

  void getMax(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  void getMin(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  void getCount(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  void echoDuplicate(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  void getIntersections(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
  void getRightShapes(std::vector< Polygon >& polygons, std::ostream& out, std::istream& in);
}

#endif
