#include "commands.hpp"

namespace rav = ravinskij;

void rav::area(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  out << rav::AccumulateArea{polygons}(cmd);
}

void rav::max(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  out << rav::GetValue{polygons}("MAX", cmd);
}

void rav::min(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  out << rav::GetValue{polygons}("MIN", cmd);
}

void rav::count(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  out << rav::GetCount{polygons}(cmd);
}

