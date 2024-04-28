#include "commands.hpp"
#include <iomanip>
#include <numeric>
#include <functional>
#include <formatGuard.hpp>
#include "polygon.hpp"
#include "predicates.hpp"

void novikov::cmd::area(const subcommands_t& cmds, const poly_vec_t& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  std::function< double(double, const Polygon&) > area_accumulator;

  try
  {
    std::size_t size = std::stoul(arg);
    using namespace std::placeholders;
    AreaPredicate acc_pred = std::bind(vertexes_count, _1, size);
    area_accumulator = std::bind(cmd::acc_area_if, _1, _2, acc_pred);
  }
  catch (const std::invalid_argument&)
  {
    area_accumulator = cmds.at(arg);
  }

  FormatGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, area_accumulator) << "\n";
}

double novikov::cmd::acc_area_if(double val, const Polygon& rhs, AreaPredicate pred)
{
  return pred(rhs) ? val + get_area(rhs) : 0.0;
}

double novikov::cmd::acc_area_mean(double val, const Polygon& rhs, std::size_t size)
{
  return val + get_area(rhs) / size;
}

/*
void novikov::cmd::Area::operator()(const subcommands& cmds, const poly_vec& vec, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;

  double res{};

  try
  {
    auto cmd_func = cmds.at(arg);
    auto acc_func = std::bind(cmd_func, _1, get_area(_2));
    res = std::accumulate(vec.cbegin(), vec.cend(), 0.0, acc_func);
  }
  catch (const std::out_of_range&)
  {}

  try
  {
    std::size_t size = std::stoul(arg);
    using namespace std::placeholders;
    auto predicate = std::bind(vertexes_count, _1, size);
    auto acc_func = std::bind(acc_area_if, _1, std::bind(get_area, _2), predicate);
    res = std::accumulate(vec.cbegin(), vec.cend(), 0.0, acc_func);
  }
  catch (const std::invalid_argument&)
  {
    throw;
  }

  out << res << "\n";
}

double novikov::cmd::acc_area_if(double val, const Polygon& rhs, bool(*pred)(const Polygon&))
{
  return pred(rhs) ? val + get_area(rhs) : 0.0;
}

double novikov::cmd::acc_area_mean(double val, const Polygon& rhs, std::size_t size)
{
  return val + get_area(rhs) / size;
}*/
