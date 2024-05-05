#include "cmd.hpp"

void ishmuratov::get_area(std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  output << polygons[1].get_area() << " get_area\n";
}

void ishmuratov::get_max(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  output << polygons[0].points[1].y << " get_max\n";
}

void ishmuratov::get_min(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  output << polygons[1].points[1].x << " get_min\n";
}

void ishmuratov::count_polygons(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  output << polygons[1].points[1].y << " count_polygons\n";
}

void ishmuratov::get_less_area(const std::vector< Polygon > & polygons, std::istream & input, std::ostream &output)
{
  output << polygons[2].points[1].x <<" get_less_area\n";
}

void ishmuratov::get_max_seq(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  output << polygons[2].points[1].y << " get_max_seq\n";
}