#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <exception>
#include <string>
#include "polygon.hpp"

namespace zaparin
{
  struct InvalidCommand : public std::exception
  {
    const char* what()
    {
      return "<INVALID COMMAND>";
    }
  };

  bool isNumeric(const std::string& str);

  void cmdArea(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out, std::string&& parameter);
  void cmdMax(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out, std::string&& parameter);
}

#endif
