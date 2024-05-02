#include "commands.hpp"
#include "polygon.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <numeric>
#include <string>

void ibragimov::calculateArea(const std::map< std::string, std::function< bool(Polygon) > >& options,
                              const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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

  using namespace std::placeholders;
  std::function< double(double, const Polygon&) > sumArea
      = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));

  std::vector< Polygon > test = {};
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(test), predicate);
  out << std::accumulate(test.begin(), test.end(), 0.0, sumArea) << '\n';
}

void ibragimov::strategies::Max::compare(const std::vector< Polygon >& polygons, const std::function< bool(Polygon, Polygon) >& comparator,
                                         std::ostream& out)
{
  out << getSize(*std::max_element(polygons.begin(), polygons.end(), comparator)) << '\n';
}

void ibragimov::strategies::Min::compare(const std::vector< Polygon >& polygons, const std::function< bool(Polygon, Polygon) >& comparator,
                                         std::ostream& out)
{
  out << getArea(*std::min_element(polygons.begin(), polygons.end(), comparator)) << '\n';
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
