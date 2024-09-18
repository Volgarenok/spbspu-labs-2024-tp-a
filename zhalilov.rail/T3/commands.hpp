#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>

namespace zhalilov
{
  struct Polygon;

  void area(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void max(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void min(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void count(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void maxSeq(const std::vector< Polygon > &, std::istream &, std::ostream &);
  void inFrame(const std::vector< Polygon > &, std::istream &, std::ostream &);
}

#endif
