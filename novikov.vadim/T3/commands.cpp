#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <functional>
#include <formatGuard.hpp>
#include "polygon.hpp"
#include "predicates.hpp"

void novikov::cmd::area(const area_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function< double(double, const Polygon&) > area_accumulator;

  try
  {
    std::size_t size = std::stoul(arg);
    using namespace std::placeholders;
    Predicate acc_pred = std::bind(vertexes_count, _1, size);
    area_accumulator = std::bind(cmd::acc_area_if, _1, _2, acc_pred);
  }
  catch (const std::invalid_argument&)
  {
    area_accumulator = args.at(arg);
  }

  FormatGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, area_accumulator) << "\n";
}

double novikov::cmd::acc_area_if(double val, const Polygon& rhs, Predicate pred)
{
  return pred(rhs) ? val + get_area(rhs) : val;
}

double novikov::cmd::acc_area_mean(double val, const Polygon& rhs, std::size_t size)
{
  return val + get_area(rhs) / size;
}

void novikov::cmd::max(const max_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  args.at(arg)(vec, out);
}

void novikov::cmd::max_area(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::max_element(vec.cbegin(), vec.cend(), compare_areas);
  out << std::setprecision(1) << std::fixed;
  out << (res != vec.cend() ? get_area(*res) : 0.0) << "\n";
}

void novikov::cmd::max_vertexes(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::max_element(vec.cbegin(), vec.cend(), compare_vertexes);
  out << (res != vec.cend() ? res->points.size() : 0) << "\n";
}

void novikov::cmd::min(const min_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  args.at(arg)(vec, out);
}

void novikov::cmd::min_area(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::min_element(vec.cbegin(), vec.cend(), compare_areas);
  out << std::setprecision(1) << std::fixed;
  out << (res != vec.cend() ? get_area(*res) : 0.0) << "\n";
}

void novikov::cmd::min_vertexes(const poly_vec_t& vec, std::ostream& out)
{
  FormatGuard guard(out);
  auto res = std::min_element(vec.cbegin(), vec.cend(), compare_vertexes);
  out << (res != vec.cend() ? res->points.size() : 0) << "\n";
}

void novikov::cmd::count(const count_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function< bool(const Polygon&) > count_pred;

  try
  {
    std::size_t size = std::stoul(arg);
    using namespace std::placeholders;
    count_pred = std::bind(vertexes_count, _1, size);
  }
  catch (const std::invalid_argument&)
  {
    count_pred = args.at(arg);
  }

  FormatGuard guard(out);
  out << std::count_if(vec.cbegin(), vec.cend(), count_pred) << "\n";
}
