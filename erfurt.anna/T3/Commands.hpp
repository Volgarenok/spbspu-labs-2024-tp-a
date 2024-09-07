#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"

namespace erfurt
{
  void makeArea(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
  void makeMax(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
  void makeMin(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
  void makeCount(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
  void makePerms(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
  void makeRmecho(std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
}

#endif
