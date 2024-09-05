#include "cmd.hpp"
#include <algorithm>
#include <numeric>
#include <functional>

void ishmuratov::get_areas(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  std::string cmd = "";
  std::vector< Polygon > eligible;
  input >> cmd;
  if (cmd == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(eligible), is_even);
  }
  else if (cmd == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(eligible), is_odd);
  }
  else if (cmd == "MEAN")
  {
    eligible = polygons;
  }
  else
  {
    size_t num = std::stoll(cmd);
    if (num < 3)
    {
      throw std::out_of_range("<INVALID COMMAND>");
    }
    auto pred = std::bind(check_size, std::placeholders::_1, num);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(eligible), pred);
  }
  std::vector< double > areas(eligible.size());
  std::transform(eligible.begin(), eligible.end(), areas.begin(), get_area);
  double area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (cmd == "MEAN")
  {
    if (eligible.empty())
    {
      throw std::out_of_range("<INVALID COMMAND>");
    }
    output << area / eligible.size() << "\n";
  }
  else
  {
    output << area << "\n";
  }
}

bool ishmuratov::is_even(const ishmuratov::Polygon & poly)
{
  return poly.points.size() % 2 == 0;
}

bool ishmuratov::is_odd(const ishmuratov::Polygon & poly)
{
  return poly.points.size() % 2 == 1;
}

bool ishmuratov::check_size(const ishmuratov::Polygon & poly, size_t num)
{
  return poly.points.size() == num;
}

void ishmuratov::get_max(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  std::string cmd = "";
  input >> cmd;
  if (polygons.empty())
  {
    throw std::out_of_range("<INVALID COMMAND>");
  }
  if (cmd == "AREA")
  {
    auto result = std::max_element(polygons.cbegin(), polygons.cend(), compare_area);
    output << get_area(*result) << "\n";
  }
  else if (cmd == "VERTEXES")
  {
    auto result = std::max_element(polygons.cbegin(), polygons.cend(), compare_vertexes);
    output << (*result).points.size() << "\n";
  }
}

void ishmuratov::get_min(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  std::string cmd = "";
  input >> cmd;
  if (polygons.empty())
  {
    throw std::out_of_range("<INVALID COMMAND>");
  }
  if (cmd == "AREA")
  {
    auto result = std::min_element(polygons.cbegin(), polygons.cend(), compare_area);
    output << get_area(*result) << "\n";
  }
  else if (cmd == "VERTEXES")
  {
    auto result = std::min_element(polygons.cbegin(), polygons.cend(), compare_vertexes);
    output << (*result).points.size() << "\n";
  }
}

size_t ishmuratov::count_points(const ishmuratov::Polygon &poly)
{
  return poly.points.size();
}

bool ishmuratov::compare_area(const ishmuratov::Polygon &poly1, const ishmuratov::Polygon &poly2)
{
  return get_area(poly1) < get_area(poly2);
}

bool ishmuratov::compare_vertexes(const ishmuratov::Polygon &poly1, const ishmuratov::Polygon &poly2)
{
  return poly1.points.size() < poly2.points.size();
}

void ishmuratov::count_polygons(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  std::string cmd = "";
  input >> cmd;
  std::vector< Polygon > to_count;
  if (cmd == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(to_count), is_even);
  }
  else if (cmd == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(to_count), is_odd);
  }
  else
  {
    size_t num = std::stoll(cmd);
    if (num < 3)
    {
      throw std::out_of_range("<INVALID COMMAND>");
    }
    auto pred = std::bind(check_size, std::placeholders::_1, num);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(to_count), pred);
  }
  output << to_count.size() << "\n";
}

void ishmuratov::get_less_area(const std::vector< Polygon > & polygons, std::istream & input, std::ostream &output)
{
  Polygon to_compare;
  std::vector< Polygon > eligible;
  input >> to_compare;
  if (!input || input.peek() != '\n')
  {
    throw std::out_of_range("<INVALID COMMAND>");
  }
  auto pred = std::bind(compare_area, std::placeholders::_1, to_compare);
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(eligible), pred);
  output << eligible.size() << "\n";
}

void ishmuratov::get_max_seq(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  Polygon to_compare;
  std::vector< size_t > sequences;
  EqualCounter counter;
  input >> to_compare;
  if (!input || input.peek() != '\n')
  {
    throw std::out_of_range("<INVALID COMMAND>");
  }
  auto pred = std::bind(counter , std::placeholders::_1, to_compare);
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(sequences), pred);
  output << *std::max_element(sequences.cbegin(), sequences.cend()) << "\n";
}

ishmuratov::EqualCounter::EqualCounter():
  count_(0)
{}

size_t ishmuratov::EqualCounter::operator()(ishmuratov::Polygon poly1, ishmuratov::Polygon poly2)
{
  if (poly1 == poly2)
  {
    count_ += 1;
    return count_;
  }
  else
  {
    size_t result = count_;
    count_ = 0;
    return result;
  }
}
