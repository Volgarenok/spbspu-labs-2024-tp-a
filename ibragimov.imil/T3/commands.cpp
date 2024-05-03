#include "commands.hpp"
#include "polygon.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <numeric>
#include <string>

void ibragimov::calculateArea(const std::map< std::string, std::function< bool(Polygon) > >& options,
                              const std::map< std::string, std::function< double(std::vector< Polygon >) > >& strategies,
                              const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string input = "";
  in >> input;

  std::function< bool(Polygon) > predicate;
  std::function< double(std::vector< Polygon >) > strategy;

  try
  {
    if (std::all_of(input.begin(), input.end(), isdigit))
    {
      using namespace std::placeholders;
      predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::stoull(input));
      strategy = strategies::Sum;
    }
    else
    {
      predicate = options.at(input);
      strategy = strategies.at(input);
    }
  }
  catch (...)
  {
    throw;
  }

  std::vector< Polygon > correct = {};
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(correct), predicate);
  out << strategy(correct) << '\n';
}

void ibragimov::findMax(const std::map< std::string, std::function< bool(Polygon, Polygon) > >& options,
                        const std::map< std::string, std::function< void(Polygon, std::ostream&) > >& strategies,
                        const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon, Polygon) > comparator;
  std::function< void(Polygon, std::ostream&) > strategy;

  std::string input = "";
  in >> input;

  try
  {
    comparator = options.at(input);
    strategy = strategies.at(input);
  }
  catch (...)
  {
    throw;
  }

  strategy(*std::max_element(polygons.begin(), polygons.end(), comparator), out);
}
void ibragimov::findMin(const std::map< std::string, std::function< bool(Polygon, Polygon) > >& options,
                        const std::map< std::string, std::function< void(Polygon, std::ostream&) > >& strategies,
                        const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon, Polygon) > comparator;
  std::function< void(Polygon, std::ostream&) > strategy;

  std::string input = "";
  in >> input;

  try
  {
    comparator = options.at(input);
    strategy = strategies.at(input);
  }
  catch (...)
  {
    throw;
  }

  strategy(*std::min_element(polygons.begin(), polygons.end(), comparator), out);
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

double ibragimov::strategies::Sum(const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  auto sum = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, sum);
}

double ibragimov::strategies::Mean(const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  auto sum = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, sum) / polygons.size();
}
void ibragimov::strategies::Size(const Polygon& polygon, std::ostream& out)
{
  out << getSize(polygon) << '\n';
}
void ibragimov::strategies::Area(const Polygon& polygon, std::ostream& out)
{
  out << getArea(polygon) << '\n';
}
