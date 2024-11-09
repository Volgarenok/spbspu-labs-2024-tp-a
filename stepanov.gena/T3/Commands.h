#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <ostream>
#include <map>
#include "DataStruct.h"


namespace stepanov
{
  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
  void rmEcho(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
  void getRects(const std::vector< Polygon >& polygons, std::ostream& out);
  void getIntersections(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);

  class Commands
  {
    public:
      Commands();
      using polys = std::vector< Polygon >&;
      void doCommand(const polys polygons, const std::string& cmd, std::ostream& out) const;
      void doCommand(const polys polygons, const std::string& cmd, size_t count, std::ostream& out) const;
      void doCommand(polys polygons, const std::string& cmd, const Polygon& polygon, std::ostream& out) const;
    private:
      using com1 = void (*)(const std::vector< Polygon >& polygons, std::ostream& out);
      using com2 = void (*)(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
      using com3 = void (*)(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
      std::map< std::string, com1 > dict1_;
      std::map< std::string, com2 > dict2_;
      std::map< std::string, com3 > dict3_;
  };

}

#endif
