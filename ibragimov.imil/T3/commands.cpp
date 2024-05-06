#include "commands.hpp"

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <iomanip>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include "outputFormatters.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include <streamGuard.hpp>

bool test(const ibragimov::Polygon& lhs, const ibragimov::Polygon& rhs)
{
  using namespace std::placeholders;
  using namespace ibragimov;
  auto isEqualX = std::bind(std::equal_to< int >{}, std::bind(getX, _1), std::bind(getX, _2));
  auto isEqualY = std::bind(std::equal_to< int >{}, std::bind(getY, _1), std::bind(getY, _2));
  auto comparePoints = std::bind(std::logical_and<>{}, std::bind(isEqualX, _1, _2), std::bind(isEqualY, _1, _2));
  return std::is_permutation(std::begin(lhs.points), std::end(lhs.points), std::begin(rhs.points), std::end(rhs.points), comparePoints);
}

double calculateAngle(const ibragimov::Point& lhs, const ibragimov::Point& rhs)
{
  using namespace std::placeholders;
  using namespace ibragimov;
  auto dot = std::bind(std::plus< int >{}, std::bind(std::multiplies< int >{}, std::bind(getX, _1), std::bind(getX, _2)),
                       std::bind(std::multiplies< int >{}, std::bind(getY, _1), std::bind(getY, _2)));
  auto det = std::bind(std::minus< int >{}, std::bind(std::multiplies< int >{}, std::bind(getX, _1), std::bind(getY, _2)),
                       std::bind(std::multiplies< int >{}, std::bind(getY, _1), std::bind(getX, _2)));
  return std::abs(std::atan2(det(rhs, lhs), dot(lhs, rhs)));
}

ibragimov::Point calculateSide(const ibragimov::Point& lhs, const ibragimov::Point& rhs)
{
  using namespace ibragimov;
  return Point{lhs.x - rhs.x, lhs.y - rhs.y};
}

bool test2(const ibragimov::Polygon& rhs)
{
  using namespace std::placeholders;
  using namespace ibragimov;

  std::vector< Point > points = {};
  std::copy(rhs.points.begin(), rhs.points.end(), std::back_inserter(points));
  points.push_back(points[0]);

  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), points.begin(), calculateSide);
  points.pop_back();
  points.push_back(points[0]);

  std::vector< double > angles = {};
  std::transform(next(points.cbegin()), points.cend(), points.cbegin(), std::back_inserter(angles), calculateAngle);

  double rightAngle = std::atan2(1, 0);
  auto isRightAngle = std::bind(std::equal_to< double >{}, _1, rightAngle);
  return std::any_of(angles.cbegin(), angles.cend(), isRightAngle);
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
      if (std::stoull(input) < 3)
      {
        throw std::exception();
      }
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

  try
  {
    functor(polygons, out);
  }
  catch (...)
  {
    throw;
  }
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

  if (polygons.size() == 0)
  {
    throw std::exception();
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

  std::vector< Polygon > correct = {};
  using namespace std::placeholders;
  std::function< bool(const Polygon&) > predicate = std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), input.points.size());
  std::copy_if(values.cbegin(), values.cend(), std::back_inserter(correct), predicate);
  if (correct.size() == 0)
  {
    throw std::exception();
  }

  std::function< bool(const Polygon&) > functor = std::bind(test, input, _1);
  out << std::count_if(values.begin(), values.end(), functor) << '\n';
}

void ibragimov::rightshapes(const std::vector< Polygon >& values, std::ostream& out)
{
  out << std::count_if(values.begin(), values.end(), test2) << '\n';
}

void ibragimov::strategies::SumIf(const std::vector< Polygon >& values, const std::function< bool(const Polygon&) >& predicate,
                                  std::ostream& out)
{
  std::vector< Polygon > correct = {};
  std::copy_if(values.cbegin(), values.cend(), std::back_inserter(correct), predicate);

  double area = 0.0;
  using namespace std::placeholders;
  auto sumArea = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  area = std::accumulate(correct.cbegin(), correct.cend(), 0.0, sumArea);
  out << AreaO{area} << '\n';
}
void ibragimov::strategies::Mean(const std::vector< Polygon >& values, std::ostream& out)
{
  if (values.size() == 0)
  {
    throw std::exception();
  }

  double area = 0.0;
  using namespace std::placeholders;
  auto sumArea = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  area = std::accumulate(values.cbegin(), values.cend(), 0.0, sumArea) / values.size();
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
  detail::StreamGuard sguard(out);
  out << std::fixed << std::setprecision(1) << area << '\n';
}
