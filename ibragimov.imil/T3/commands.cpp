#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <map>
#include <string>

void ibragimov::findMax(const std::map< std::string, std::function< bool(Polygon, Polygon) > >& options,
                        const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon, Polygon) > comparator;

  std::string input = "";
  in >> input;

  try
  {
    comparator = options.at(input);
  }
  catch (...)
  {
    throw;
  }

  auto output = std::max_element(polygons.begin(), polygons.end(), comparator);
  out << getSize(*output) << '\n';
}
void ibragimov::findMin(const std::map< std::string, std::function< bool(Polygon, Polygon) > >& options,
                        const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon, Polygon) > comparator;

  std::string input = "";
  in >> input;

  try
  {
    comparator = options.at(input);
  }
  catch (...)
  {
    throw;
  }

  auto output = std::min_element(polygons.begin(), polygons.end(), comparator);
  out << getSize(*output) << '\n';
}

void ibragimov::count(const std::map< std::string, std::function< bool(Polygon) > >& options, const std::vector< Polygon >& polygons,
                      std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;

  std::function< bool(Polygon) > predicate;

  try
  {
    if (std::all_of(input.begin(), input.end(), isdigit))
    {
      using namespace std::placeholders;
      predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::stoull(input));
    }
    else
    {
      predicate = options.at(input);
    }
  }
  catch (...)
  {
    throw;
  }

  out << std::count_if(polygons.begin(), polygons.end(), predicate) << '\n';
}
