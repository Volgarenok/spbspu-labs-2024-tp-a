#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <ostream>
#include <map>
#include "polygon.hpp"

namespace chernikova
{
  class Commands
  {
  public:
    Commands();
    void doCommand(const std::vector< Polygon >& polygons, const std::string& cmd, std::ostream& out) const;
    void doCommand(const std::vector< Polygon >& polygons, const std::string& cmd, size_t count, std::ostream& out) const;
    void doCommand(std::vector< Polygon >& polygons, const std::string& cmd, const Polygon& polygon, std::ostream& out) const;
    void doCommand(std::vector< Polygon >& polygons, const Commands& dict, const std::string& cmd,
      std::ostream& out, std::istream& in);
  private:
    using com1 = void (*)(const std::vector< Polygon >& polygons, std::ostream& out);
    using com2 = void (*)(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
    using com3 = void (*)(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
    std::map< std::string, com1 > dict1_;
    std::map< std::string, com2 > dict2_;
    std::map< std::string, com3 > dict3_;
  };
  std::string inputCommand(std::istream& in);
}

#endif
