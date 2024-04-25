#ifndef POLYGON_HANDLER_HPP
#define POLYGON_HANDLER_HPP

#include <exception>
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace kravchenko
{
  class InvalidCommand: public std::exception
  {
  public:
    const char* what() const noexcept override;
  };

  struct CommandArguments
  {
    std::vector< kravchenko::Polygon >& data;
    std::istream& in;
    std::ostream& out;
  };
}

#endif
