#include "commands.hpp"


void kovtun::area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::map< std::string, std::function< bool(const kovtun::Polygon & polygon) > > args
  {
    {"EVEN", isEven}
  };

  std::string arg;
  in >> arg;

  std::vector< kovtun::Polygon > selection;
  if (args.find(arg) != args.end())
  {
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), args.at(arg));
  }

  std::vector< double > result(selection.size());
  std::transform(selection.cbegin(), selection.cend(), result.begin(), getArea);
  out << std::accumulate(result.cbegin(), result.cend(), 0.0);
}

bool kovtun::isEven(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}
