#include "commands.hpp"
#include <iostream>
#include <string>
#include <numeric>
#include <iomanip>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <limits>
#include "../common/streamGuard.hpp"

void emptyCheck(const std::vector< strelyaev::Polygon >& v)
{
  if (v.empty())
  {
    throw std::logic_error("EMPTY VECTOR");
  }
}

void strelyaev::count_cmd(std::ostream& out,
    std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  using namespace std::placeholders;
  std::string str_args = "";
  in >> str_args;
  std::function< bool(const Polygon&) > pred;
  try
  {
    size_t ver = std::stoull(str_args);
    if (ver < 3)
    {
      throw std::logic_error("INVALID COMMANDS");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(size_getter, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  size_t count = std::count_if(polygons_vector.cbegin(), polygons_vector.cend(), pred);
  out << count;
}

void strelyaev::area_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector,
      const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  StreamGuard s_guard(out);
  std::function< bool(const Polygon&) > pred;
  std::string str_args = "";
  in >> str_args;
  size_t devide = 1;
  if (str_args == "MEAN")
  {
    emptyCheck(polygons_vector);
    devide = polygons_vector.size();
  }
  try
  {
    using namespace std::placeholders;
    size_t ver = std::stoull(str_args);
    if (ver < 3)
    {
      throw std::logic_error("INVALID COMMANDS");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(size_getter, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  std::vector< Polygon > area_polygons;
  std::vector< double > areas;
  std::copy_if(polygons_vector.cbegin(), polygons_vector.cend(), std::back_inserter(area_polygons), pred);
  std::transform(area_polygons.cbegin(), area_polygons.cend(), std::back_inserter(areas), get_area);
  out << std::setprecision(1);
  out << std::fixed;
  double a = std::accumulate(areas.begin(), areas.end(), 0.0) / devide;
  out << a;
}

void strelyaev::max_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector)
{
  StreamGuard s_guard(out);
  emptyCheck(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::max_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), size_getter);
    out << *std::max_element(areas.begin(), areas.end());
  }
}

void strelyaev::min_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons_vector)
{
  StreamGuard s_guard(out);
  emptyCheck(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::min_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas;
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), size_getter);
    out << *std::min_element(areas.begin(), areas.end());
  }
}

bool strelyaev::permutation_polygons(const Polygon& lhs, const Polygon& rhs)
{
  using namespace std::placeholders;
  auto compare_x = std::bind(std::equal_to< int >{}, std::bind(get_x, _1), std::bind(get_x, _2));
  auto compare_y = std::bind(std::equal_to< int >{}, std::bind(get_y, _1), std::bind(get_y, _2));
  auto compare_points = std::bind(std::logical_and<>{}, std::bind(compare_x, _1, _2), std::bind(compare_y, _1, _2));
  return std::is_permutation(rhs.points.cbegin(), rhs.points.cend(), lhs.points.cbegin(), lhs.points.cend(), compare_points);
}

void strelyaev::perms_cmd(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polys)
{
  emptyCheck(polys);
  Polygon poly;
  in >> poly;
  std::vector< Polygon > correct;
  using namespace std::placeholders;
  std::function< bool(const Polygon&) > pred = std::bind(std::equal_to< size_t >{}, std::bind(size_getter, _1), poly.points.size());
  std::copy_if(polys.cbegin(), polys.cend(), std::back_inserter(correct), pred);
  if (correct.empty())
  {
    throw std::out_of_range("Something is wrong with a command");
  }
  pred = std::bind(permutation_polygons, poly, _1);
  out << std::count_if(correct.cbegin(), correct.cend(), pred);
}

size_t strelyaev::isEqualCounter(const Polygon& p1, const Polygon& p2, size_t& counter)
{
  if (p1 == p2)
  {
    counter++;
  }
  else
  {
    counter = 0;
  }
  return counter;
}

void strelyaev::maxseq_cmd(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector)
{
  emptyCheck(polygons_vector);
  size_t verts = 0;
  in >> verts;
  if (verts < 3)
  {
    throw std::logic_error("INVALID VERTS");
  }
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >(in), (verts - 1), std::back_inserter(points));
  if (in.peek() != '\n')
  {
    std::copy_n(std::istream_iterator< Point >(in), 1, std::back_inserter(points));
  }
  Polygon poly;
  if (in && points.size() == verts)
  {
    poly.points = points;
    if (in.peek() != '\n')
    {
      in.setstate(std::ios::failbit);
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  if (in.fail())
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    throw std::logic_error("INVALID MAXSEQ");
  }
  std::vector< size_t > sequences;
  size_t counter = 0;
  using namespace std::placeholders;
  auto func = std::bind(isEqualCounter, _1, poly, counter);
  std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(sequences), func);
  out << *std::max_element(sequences.cbegin(), sequences.cend());
}

