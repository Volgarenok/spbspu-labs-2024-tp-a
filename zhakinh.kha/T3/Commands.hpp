#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <functional>
#include <iomanip>
#include "streamGuard.hpp"
#include "polygon.hpp"
#include "Utilies.hpp"

namespace zhakha
{
  enum EmptyVectors
  {
    Disabled,
    Enabled
  };

  struct AreaCalculator
  {
    std::function< double(const Polygon&) > calculate;
    EmptyVectors empty_vector_support;
  };

  using poly_vec_t = std::vector< Polygon >;

  namespace cmd
  {
    using area_args_t = std::unordered_map< std::string, AreaCalculator >;
    void area(const area_args_t& cmds, const poly_vec_t& vec, std::istream& in, std::ostream& out);

    using minmax_args_t = std::unordered_map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >;
    void minmax(const minmax_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out);

    using count_args_t = std::unordered_map< std::string, std::function< bool(const Polygon&) > >;
    void count(const count_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out);

    void echo(poly_vec_t& vec, std::istream& in, std::ostream& out);
    void inFrame(const poly_vec_t& vec, std::istream& in, std::ostream& out);
  }

  using predicate_t = std::function< bool(const Polygon&) >;
  double calculateAreaIf(const Polygon& polygon, predicate_t pred);
  double calculateMeanArea(const Polygon& polygon, size_t size);

  using comparator_t = std::function< bool(const Polygon&, const Polygon&) >;
  using poly_vec_it_t = poly_vec_t::const_iterator;

  struct Max
  {
    poly_vec_it_t operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp);
  };

  struct Min
  {
    poly_vec_it_t operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp);
  };

  template< typename FindTheMost >
  void minmaxArea(const poly_vec_t& vec, std::ostream& out)
  {
    StreamGuard guard(out);
    auto res = FindTheMost()(vec.cbegin(), vec.cend(), compareAreas);
    out << std::setprecision(1) << std::fixed;
    out << getArea(*res) << "\n";
  }

  template< typename FindTheMost >
  void minmaxVertexes(const poly_vec_t& vec, std::ostream& out)
  {
    StreamGuard guard(out);
    auto res = FindTheMost()(vec.cbegin(), vec.cend(), compareVertexes);
    out << res->points.size() << "\n";
  }

  struct EntryDuplicator
  {
    poly_vec_t& vec;
    const Polygon& arg;
    Polygon operator()(Polygon&& polygon);
  };

    Polygon getFrameRect(const poly_vec_t& vec);
}

#endif
