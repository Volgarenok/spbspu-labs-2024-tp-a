#include "commands.hpp"
#include <iomanip>
#include <scopeGuard.hpp>

namespace rav = ravinskij;

void rav::area(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1) << rav::AccumulateArea{polygons}(cmd);
}

void rav::max(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetValue{polygons}("MAX", cmd);
}

void rav::min(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetValue{polygons}("MIN", cmd);
}

void rav::count(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetCount{polygons}(cmd);
}

