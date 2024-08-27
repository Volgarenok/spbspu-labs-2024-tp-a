#ifndef CMD_HPP
#define CMD_HPP

#include "polygon.hpp"

namespace ishmuratov
{
  void get_areas(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void get_max(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void get_min(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void count_polygons(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);
  void get_less_area(const std::vector< Polygon > & polygons, std::istream & input, std::ostream &output);
  void get_max_seq(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output);

  bool is_even(const Polygon & poly);
  bool is_odd(const Polygon & poly);
  bool check_size(const Polygon & poly, size_t num);
  bool compare_area(const Polygon & poly1, const Polygon & poly2);
  bool compare_vertexes(const Polygon & poly1, const Polygon & poly2);
  size_t count_points(const Polygon & poly);

  struct EqualCounter
  {
    EqualCounter();
    size_t operator()(Polygon poly1, Polygon poly2);
  private:
    size_t count_;
  };
}

#endif
