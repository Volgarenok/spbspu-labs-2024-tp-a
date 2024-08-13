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

void isaychev::do_area(std::istream & in, std::ostream & out, const collection_t & col) // perepisat
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
  else if (str == "num-of-vertexes")
  {
    size_t num = 0;
    in >> num;
    auto predicate = std::bind(is_right_size, std::placeholders::_1, num);
    std::copy_if(col.cbegin(), col.cend(), std::back_inserter(temp), predicate);
  }
  else if (str == "MEAN")
  {
    out << get_areas_sum(col) / col.size() << "\n";
  }
  else
  {
    throw std::invalid_argument("wrong specifier");
  }
  if (!temp.empty())
  {
    out << get_areas_sum(temp) << "\n";
  }
}

void isaychev::do_max(std::istream & in , std::ostream & out, const collection_t & col)
{
  std::string str;
  in >> str;
  if (str == "AREA")
  {
    std::vector< double > areas;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(areas), get_area);
    out << *(std::max_element(areas.cbegin(), areas.cend())) << "\n";
  }
  else if (str == "VERTEXES")
  {
    std::vector< size_t > vertexes;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(vertexes), get_vertex);
    out << *(std::max_element(vertexes.cbegin(), vertexes.cend())) << "\n";
  }
  else
  {
    throw std::invalid_argument("wrong specifier");
  }
}

void isaychev::do_min(std::istream & in, std::ostream & out, const collection_t & col)
{ //можно объеденить в одну ф-цию потом разделить в мапе (наверно)
  std::string str;
  in >> str;
  if (str == "AREA")
  {
    std::vector< double > areas;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(areas), get_area);
    out << *(std::min_element(areas.cbegin(), areas.cend())) << "\n";
  }
  else if (str == "VERTEXES")
  {
    std::vector< size_t > vertexes;
    std::transform(col.cbegin(), col.cend(), std::back_inserter(vertexes), get_vertex);
    out << *(std::min_element(vertexes.cbegin(), vertexes.cend())) << "\n";
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
    out << std::count_if(col.cbegin(), col.cend(), is_even) << "\n";
  }
  else if (str == "ODD")
  {
    out << std::count_if(col.cbegin(), col.cend(), is_odd) << "\n";
  }
  else if (str == "num-of-vertexes")
  {
    size_t num = 0;
    in >> num;
    auto predicate = std::bind(is_right_size, std::placeholders::_1, num);
    out << std::count_if(col.cbegin(), col.cend(), predicate) << "\n";
  }
  else
  {
    throw std::invalid_argument("wrong specifier");
  }
}

void isaychev::do_maxseq(std::istream & in, std::ostream & out, const collection_t & col)
{
  Polygon pol;
  in >> pol;
  if (!in)
  {
    throw std::invalid_argument("wrong polygon input");
  }
  std::vector< size_t > seqs;
  std::transform(col.cbegin(), col.cend(), std::back_inserter(seqs), EqualCounter(pol));
  out << *(std::max_element(seqs.cbegin(), seqs.cend())) << "\n";
}
