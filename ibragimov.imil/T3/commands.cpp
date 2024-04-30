#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <map>
#include <string>

void ibragimov::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;

  std::function< bool(size_t) > predicate;
  std::map< std::string, std::function< bool(size_t) > > predicates;
  {
    using namespace std::placeholders;
    predicates["EVEN"] = std::bind(std::equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, _1, 2), 0);
    predicates["ODD"] = std::bind(std::not_equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, _1, 2), 0);
  }

  try
  {
    if (std::all_of(input.begin(), input.end(), isdigit))
    {
      size_t n = std::stoull(input);
      using namespace std::placeholders;
      predicate = std::bind(std::equal_to< size_t >{}, _1, n);
    }
    else
    {
      predicate = predicates.at(input);
    }
  }
  catch (...)
  {
    throw;
  }

  out << std::count_if(polygons.begin(), polygons.end(), [&predicate](const Polygon& p) {
    return predicate(p.points.size());
  }) << '\n';
}

// double ibragimov::findMax(const std::vector< Polygon >& polygons)
// {
//   return 2;
// }
//
// double ibragimov::findMin(const std::vector< Polygon >& polygons)
// {
//   return 3;
// }
//
// double ibragimov::count(const std::vector< Polygon >& polygons)
// {
//   return 4;
// }
