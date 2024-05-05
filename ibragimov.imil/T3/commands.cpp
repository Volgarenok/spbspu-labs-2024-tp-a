#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include "outputFormatters.hpp"
#include "polygon.hpp"

bool test(const ibragimov::Polygon& lhs, const ibragimov::Polygon& rhs)
{
  using namespace std::placeholders;
  using namespace ibragimov;
  auto isEqualX = std::bind(std::equal_to< int >{}, std::bind(getX, _1), std::bind(getX, _2));
  auto isEqualY = std::bind(std::equal_to< int >{}, std::bind(getY, _1), std::bind(getY, _2));
  auto comparePoints = std::bind(std::logical_and{}, std::bind(isEqualX, _1, _2), std::bind(isEqualY, _1, _2));
  return std::is_permutation(std::begin(lhs.points), std::end(lhs.points), std::begin(rhs.points), std::end(rhs.points), comparePoints);
}

void ibragimov::calculateArea(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >& functors,
                              const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< void(const std::vector< Polygon >&, std::ostream&) > functor;

  std::string input = "";
  in >> input;
  try
  {
    if (std::all_of(input.begin(), input.end(), isdigit))
    {
      using namespace std::placeholders;
      std::function< bool(const Polygon&) > predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::stoull(input));
      functor = std::bind(strategies::SumIf, _1, predicate, _2);
    }
    else
    {
      functor = functors.at(input);
    }
  }
  catch (...)
  {
    throw;
  }

  functor(polygons, out);
}

void ibragimov::find(const std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >& functors,
                     const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< void(const std::vector< Polygon >&, std::ostream&) > functor;

  std::string input = "";
  in >> input;
  try
  {
    functor = functors.at(input);
  }
  catch (...)
  {
    throw;
  }

  functor(polygons, out);
}

void ibragimov::count(const std::map< std::string, std::function< bool(const Polygon&) > >& functors,
                      const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::function< bool(Polygon) > functor;

  std::string input = "";
  in >> input;
  try
  {
    if (std::all_of(input.begin(), input.end(), isdigit))
    {
      using namespace std::placeholders;
      functor = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), std::stoull(input));
    }
    else
    {
      functor = functors.at(input);
    }
  }
  catch (...)
  {
    throw;
  }

  out << std::count_if(polygons.begin(), polygons.end(), functor) << '\n';
}

void ibragimov::perms(const std::vector< Polygon >& values, std::istream& in, std::ostream& out)
{
  Polygon input;
  in >> input;

  using namespace std::placeholders;
  std::function< bool(const Polygon&) > functor = std::bind(test, input, _1);
  out << std::count_if(values.begin(), values.end(), functor);
}

void ibragimov::strategies::SumIf(const std::vector< Polygon >& values, const std::function< bool(const Polygon&) >& predicate,
                                  std::ostream& out)
{
  std::vector< Polygon > correct = {};
  std::copy_if(values.begin(), values.end(), std::back_inserter(correct), predicate);
  using namespace std::placeholders;
  auto sum = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  double area = std::accumulate(correct.begin(), correct.end(), 0.0, sum);
  out << AreaO{area} << '\n';
}
void ibragimov::strategies::Mean(const std::vector< Polygon >& values, std::ostream& out)
{
  using namespace std::placeholders;
  auto sum = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  double area = std::accumulate(values.begin(), values.end(), 0.0, sum) / values.size();
  out << AreaO{area} << '\n';
}

ibragimov::Polygon ibragimov::strategies::Max(const std::vector< Polygon >& values,
                                              const std::function< bool(const Polygon&, const Polygon&) >& comparator)
{
  return *std::max_element(values.begin(), values.end(), comparator);
}
ibragimov::Polygon ibragimov::strategies::Min(const std::vector< Polygon >& values,
                                              const std::function< bool(const Polygon&, const Polygon&) >& comparator)
{
  return *std::min_element(values.begin(), values.end(), comparator);
}
void ibragimov::strategies::Vertexes(const Polygon& value, std::ostream& out)
{
  out << getSize(value) << '\n';
}
void ibragimov::strategies::Area(const Polygon& value, std::ostream& out)
{
  double area = getArea(value);
  out << AreaO{area} << '\n';
}
