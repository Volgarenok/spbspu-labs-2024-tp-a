#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <map>
#include <functional>
#include "polygon.hpp"

namespace novikov
{
  namespace cmd
  {
    using subcommands_t = std::map< std::string, std::function< double(double, const Polygon&) > >;
    using poly_vec_t = std::vector< Polygon >;

    void area(const subcommands_t& cmds, const poly_vec_t& vec, std::istream& in, std::ostream& out);
    using AreaPredicate = std::function< bool(const Polygon&) >;
    double acc_area_if(double val, const Polygon& rhs, AreaPredicate pred);
    double acc_area_mean(double val, const Polygon& rhs, std::size_t size);
  }
}

#endif
