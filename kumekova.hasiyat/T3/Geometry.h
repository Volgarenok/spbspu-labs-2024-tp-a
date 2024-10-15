#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Polygon.h"
#include <string>
#include <vector>

namespace kumekova {
double polygonArea(const Polygon &polygon);
void areaCommand(const std::vector<Polygon> &polygons, const std::string &type);
void maxCommand(const std::vector<Polygon> &polygons, const std::string &type);
void minCommand(const std::vector<Polygon> &polygons, const std::string &type);
void countCommand(const std::vector<Polygon> &polygons,
                  const std::string &type);

std::vector<Polygon> readPolygons(const std::string &filename);
} // namespace kumekova

#endif
