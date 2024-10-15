#include "Geometry.h"
#include "Polygon.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

namespace kumekova {
std::vector<Polygon> readPolygons(const std::string &filename) {
  std::ifstream file(filename);
  std::vector<Polygon> polygons;
  if (!file.is_open()) {
    std::cerr << "The file could not be opened " << filename << "\n";
    return polygons;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    Polygon polygon;
    int numVertices;
    char ch;
    if (!(iss >> numVertices)) {
      continue;
    }
    for (int i = 0; i < numVertices; ++i) {
      Point p;
      if (!(iss >> ch >> p.x >> ch >> p.y >> ch)) {
        polygon.points.clear();
        break;
      }
      polygon.points.push_back(p);
    }
    if (!polygon.points.empty()) {
      polygons.push_back(polygon);
    }
  }
  return polygons;
}

double polygonArea(const Polygon &polygon) {
  double area = 0;
  int n = polygon.points.size();
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    area += polygon.points[i].x * polygon.points[j].y -
            polygon.points[j].x * polygon.points[i].y;
  }
  return std::abs(area) / 2.0;
}
// Команда AREA <EVEN|ODD|MEAN|num-of-vertexes>
void areaCommand(const std::vector<Polygon> &polygons,
                 const std::string &type) {
  if (type == "EVEN" || type == "ODD") {
    double totalArea = 0;
    for (const auto &polygon : polygons) {
      if ((polygon.points.size() % 2 == 0 && type == "EVEN") ||
          (polygon.points.size() % 2 != 0 && type == "ODD")) {
        totalArea += polygonArea(polygon);
      }
    }
    std::cout << totalArea << "\n";
  } else if (type == "MEAN") {
    double totalArea = 0;
    for (const auto &polygon : polygons) {
      totalArea += polygonArea(polygon);
    }
    if (!polygons.empty()) {
      std::cout << totalArea / polygons.size() << "\n";
    }
  } else {
    std::size_t numVertices = std::stoul(type);
    double totalArea = 0;
    for (const auto &polygon : polygons) {
      if (polygon.points.size() == numVertices) {
        totalArea += polygonArea(polygon);
      }
    }
    std::cout << totalArea << "\n";
  }
}
// Команда MAX <AREA|VERTEXES>
void maxCommand(const std::vector<Polygon> &polygons, const std::string &type) {
  if (type == "AREA") {
    double maxArea = 0;
    for (const auto &polygon : polygons) {
      double area = polygonArea(polygon);
      if (area > maxArea) {
        maxArea = area;
      }
    }
    std::cout << maxArea << "\n";
  } else if (type == "VERTEXES") {
    std::size_t maxVertices = 0;
    for (const auto &polygon : polygons) {
      if (polygon.points.size() > maxVertices) {
        maxVertices = polygon.points.size();
      }
    }
    std::cout << maxVertices << "\n";
  }
}
// Команда MIN <AREA|VERTEXES>
void minCommand(const std::vector<Polygon> &polygons, const std::string &type) {
  if (type == "AREA") {
    double minArea = std::numeric_limits<double>::max();
    for (const auto &polygon : polygons) {
      double area = polygonArea(polygon);
      if (area < minArea) {
        minArea = area;
      }
    }
    std::cout << minArea << "\n";
  } else if (type == "VERTEXES") {
    std::size_t minVertices = std::numeric_limits<std::size_t>::max();
    for (const auto &polygon : polygons) {
      if (polygon.points.size() < minVertices) {
        minVertices = polygon.points.size();
      }
    }
    std::cout << minVertices << "\n";
  }
}
// Команда COUNT <EVEN|ODD|num-of-vertexes>
void countCommand(const std::vector<Polygon> &polygons,
                  const std::string &type) {
  if (type == "EVEN" || type == "ODD") {
    int count = 0;
    for (const auto &polygon : polygons) {
      if ((polygon.points.size() % 2 == 0 && type == "EVEN") ||
          (polygon.points.size() % 2 != 0 && type == "ODD")) {
        count++;
      }
    }
    std::cout << count << "\n";
  } else {
    std::size_t numVertices = std::stoul(type);
    int count = 0;
    for (const auto &polygon : polygons) {
      if (polygon.points.size() == numVertices) {
        count++;
      }
    }
    std::cout << count << "\n";
  }
}
} // namespace kumekova
