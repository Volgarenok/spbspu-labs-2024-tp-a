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

  namespace detail
  {
    template <class UnaryPredicate>
    double getAreaIf(const std::vector<Polygon>& poly, UnaryPredicate pred)
    {
      std::vector< Polygon > polygon;
      std::copy_if(poly.cbegin(), poly.cend(), std::back_inserter(polygon), pred);
      return getAreaPolygons(polygon);
    }
  }
}

#endif
