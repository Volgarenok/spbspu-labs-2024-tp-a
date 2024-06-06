#ifndef CMD_HPP
#define CMD_HPP

#include "polygon.hpp"

namespace ishmuratov
{
  void get_area(std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void get_max(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void get_min(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void count_polygons(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void get_less_area(const std::vector< Polygon > & polygons, std::istream & input, std::ostream &output);
  void get_max_seq(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
}

#endif
