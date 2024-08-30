#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

void checkEmpty(const std::vector< allaberdiev::Polygon >& v)
{
  if (v.empty())
  {
    throw std::logic_error("EMPTY VECTOR");
  }
}

void allaberdiev::count(std::ostream& out,
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
    pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  size_t count = std::count_if(polygons_vector.cbegin(), polygons_vector.cend(), pred);
  out << count;
}

void allaberdiev::getArea(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  std::function< bool(const Polygon&) > pred;
  std::string str_args = "";
  in >> str_args;
  size_t devide = 1;
  if (str_args == "MEAN")
  {
    checkEmpty(polygons_vector);
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
    pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  std::vector< Polygon > area_polygons;
  std::copy_if(polygons_vector.cbegin(), polygons_vector.cend(), std::back_inserter(area_polygons), pred);
  std::vector< double > areas(area_polygons.size());
  std::transform(area_polygons.cbegin(), area_polygons.cend(), std::back_inserter(areas), get_area);
  out << std::setprecision(1);
  out << std::fixed;
  double a = std::accumulate(areas.begin(), areas.end(), 0.0) / devide;
  out << a;
}

void allaberdiev::findMax(std::ostream& out, std::istream& in, const std::vector< Polygon >& polygons_vector)
{
  checkEmpty(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::max_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_size);
    out << *std::max_element(areas.begin(), areas.end());
  }
}

void allaberdiev::findMin(std::ostream& out, std::istream& in, const std::vector< Polygon >& polygons_vector)
{
  checkEmpty(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > tmp(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(tmp), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::min_element(tmp.begin(), tmp.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > tmp(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(tmp), get_size);
    out << *std::min_element(tmp.begin(), tmp.end());
  }
}
