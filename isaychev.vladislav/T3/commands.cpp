#include "commands.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <numeric>

double get_areas_sum(const isaychev::collection_t & col)
{
  std::vector< double > areas(col.size());
  std::transform(col.cbegin(), col.cend(), areas.begin(), isaychev::get_area);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

void isaychev::do_area(std::istream & in, std::ostream & out, const collection_t & col)
{
  std::vector< Polygon > temp;
  std::string str;
  in >> str;
  if (str == "EVEN")
  {
    std::copy_if(col.cbegin(), col.cend(), std::back_inserter(temp), is_even);
  }
  else if (str == "ODD")
  {
    std::copy_if(col.cbegin(), col.cend(), std::back_inserter(temp), is_odd);
  }
  else if (str == "MEAN")
  {
    if (col.empty())
    {
      throw std::runtime_error("no polygons");
    }
    out << get_areas_sum(col) / col.size();
  }
  else
  {
    size_t num = std::stoull(str);
    if (num < 3)
    {
      throw std::logic_error("not enough vertexes");
    }
    auto predicate = std::bind(is_right_size, std::placeholders::_1, num);
    std::copy_if(col.cbegin(), col.cend(), std::back_inserter(temp), predicate);
  }
  if (str != "MEAN")
  {
    out << get_areas_sum(temp);
  }
}

void isaychev::do_max(std::istream & in, std::ostream & out, const collection_t & col)
{
  if (col.empty())
  {
    throw std::runtime_error("no polygons");
  }

  std::string str;
  in >> str;
  if (str == "AREA")
  {
    std::vector< double > areas;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(areas), get_area);
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
  else if (str == "VERTEXES")
  {
    std::vector< size_t > vertexes;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(vertexes), get_vertex);
    out << *(std::max_element(vertexes.cbegin(), vertexes.cend()));
  }
  else
  {
    throw std::invalid_argument("wrong specifier");
  }
}

void isaychev::do_min(std::istream & in, std::ostream & out, const collection_t & col)
{
  if (col.empty())
  {
    throw std::runtime_error("no polygons");
  }

  std::string str;
  in >> str;
  if (str == "AREA")
  {
    std::vector< double > areas;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(areas), get_area);
    out << *(std::min_element(areas.cbegin(), areas.cend()));
  }
  else if (str == "VERTEXES")
  {
    std::vector< size_t > vertexes;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(vertexes), get_vertex);
    out << *(std::min_element(vertexes.cbegin(), vertexes.cend()));
  }
  else
  {
    throw std::invalid_argument("wrong specifier");
  }
}

void isaychev::do_count(std::istream & in, std::ostream & out, const collection_t & col)
{
  std::string str;
  in >> str;
  if (str == "EVEN")
  {
    out << std::count_if(col.cbegin(), col.cend(), is_even);
  }
  else if (str == "ODD")
  {
    out << std::count_if(col.cbegin(), col.cend(), is_odd);
  }
  else
  {
    size_t num = std::stoull(str);
    if (num < 3)
    {
      throw std::logic_error("not enough vertexes");
    }
    auto predicate = std::bind(is_right_size, std::placeholders::_1, num);
    out << std::count_if(col.cbegin(), col.cend(), predicate);
  }
}

bool is_eol(std::istream & in)
{
  in >> std::noskipws;
  char c = 0;
  in >> c;
  in >> std::skipws;
  return c == '\n';
}

void isaychev::do_maxseq(std::istream & in, std::ostream & out, const collection_t & col)
{
  if (col.empty())
  {
    throw std::runtime_error("no polygons");
  }

  Polygon pol;
  in >> pol;
  if (!in || !is_eol(in))
  {
    throw std::invalid_argument("wrong polygon input");
  }
  std::vector< size_t > seqs;
  std::transform(col.cbegin(), col.cend(), std::back_inserter(seqs), EqualCounter(pol));
  out << *(std::max_element(seqs.cbegin(), seqs.cend()));
}

void isaychev::do_intersections(std::istream & in, std::ostream & out, const collection_t & col)
{
  if (col.empty())
  {
    throw std::runtime_error("no polygons");
  }

  Polygon pol;
  in >> pol;
  if (!in || !is_eol(in))
  {
    throw std::invalid_argument("wrong polygon input");
  }
  auto predicate = std::bind(has_intersections, std::cref(pol), std::placeholders::_1);
  out << std::count_if(col.cbegin(), col.cend(), predicate);
}
