#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <map>
#include <string>

void ibragimov::findMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon, Polygon) > comparator;
  std::map< std::string, std::function< bool(Polygon, Polygon) > > comparators;
  {
    using namespace std::placeholders;
    comparators["VERTEXES"] = std::bind(std::less< size_t >{}, std::bind(getSize, _1), std::bind(getSize, _2));
    comparators["AREA"] = std::bind(std::less< double >{}, std::bind(getArea, _1), std::bind(getArea, _2));
  }

  std::string input = "";
  in >> input;

  try
  {
    comparator = comparators.at(input);
  }
  catch (...)
  {
    throw;
  }

  auto output = std::max_element(polygons.begin(), polygons.end(), comparator);
  out << getSize(*output) << '\n';
}
void ibragimov::findMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon, Polygon) > comparator;
  std::map< std::string, std::function< bool(Polygon, Polygon) > > comparators;
  {
    using namespace std::placeholders;
    comparators["VERTEXES"] = std::bind(std::less< size_t >{}, std::bind(getSize, _1), std::bind(getSize, _2));
    comparators["AREA"] = std::bind(std::less< double >{}, std::bind(getArea, _1), std::bind(getArea, _2));
  }

  std::string input = "";
  in >> input;

  try
  {
    comparator = comparators.at(input);
  }
  catch (...)
  {
    throw;
  }

  auto output = std::min_element(polygons.begin(), polygons.end(), comparator);
  out << getSize(*output) << '\n';
}

void ibragimov::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;

  std::function< bool(Polygon) > predicate;
  std::map< std::string, std::function< bool(Polygon) > > predicates;
  {
    using namespace std::placeholders;
    predicates["EVEN"] = std::bind(std::equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
    predicates["ODD"] = std::bind(std::not_equal_to< size_t >{}, std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2), 0);
  }

  try
  {
    if (std::all_of(input.begin(), input.end(), isdigit))
    {
      size_t n = std::stoull(input);
      using namespace std::placeholders;
      predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), n);
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

  out << std::count_if(polygons.begin(), polygons.end(), predicate) << '\n';
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
