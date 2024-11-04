#include "commands.hpp"


void kovtun::area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out)
{;
  std::map< std::string, std::pair<
      std::function< bool(const kovtun::Polygon & polygon) >,
      std::function< double(const kovtun::Polygon & polygon) > > > args
  {
    {"EVEN", std::make_pair(isEven, getArea)},
    {"ODD", std::make_pair(isOdd, getArea)},
    {"MEAN", std::make_pair(notEmpty, getArea)}
  };

  std::string arg;
  in >> arg;

  std::vector< kovtun::Polygon > selection;
  if (args.find(arg) == args.end())
  {
    // TODO: vertexes
  }

  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selection), args.at(arg).first);
  if (selection.empty())
  {
    throw std::invalid_argument("none of the polygons met the criteria");
  }

  std::vector< double > result(selection.size());
  std::transform(selection.cbegin(), selection.cend(), result.begin(), getArea);
  out << std::accumulate(result.cbegin(), result.cend(), 0.0);
}

bool kovtun::isEven(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 == 0 && notEmpty(polygon);
}

bool kovtun::isOdd(const kovtun::Polygon & polygon)
{
  return polygon.points.size() % 2 != 0 && notEmpty(polygon);
}

bool kovtun::notEmpty(const kovtun::Polygon & polygon)
{
  return !polygon.points.empty();
}


