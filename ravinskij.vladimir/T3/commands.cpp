#include "commands.hpp"

namespace rav = ravinskij;

void rav::area(const std::vector <Polygon>& polygons, std::istream& in, std::ostream& out)
{
  out << polygons.size();
  std::string str;
  in >> str;
  out << str;
}

void rav::max(const std::vector <Polygon>& polygons, std::istream& in, std::ostream& out)
{
  out << polygons.size();
  std::string str;
  in >> str;
  out << str;
}

void rav::min(const std::vector <Polygon>& polygons, std::istream& in, std::ostream& out)
{
  out << polygons.size();
  std::string str;
  in >> str;
  out << str;
}

void rav::count(const std::vector <Polygon>& polygons, std::istream& in, std::ostream& out)
{
  out << polygons.size();
  std::string str;
  in >> str;
  out << str;
}

