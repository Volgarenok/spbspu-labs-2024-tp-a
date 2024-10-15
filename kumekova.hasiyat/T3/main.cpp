#include "Geometry.h"
#include "Polygon.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

int main() {
  std::string filename;
  std::cout << "Enter the file name: ";
  std::cin >> filename;
  std::vector<kumekova::Polygon> polygons = kumekova::readPolygons(filename);
  if (polygons.empty()) {
    std::cerr << "The file is empty or contains incorrect data\n";
    return 1;
  }
  std::string command;

  while (true) {
    std::cout << "Enter the command: ";
    std::cin >> command;
    if (command == "AREA") {
      std::string type;
      std::cin >> type;
      kumekova::areaCommand(polygons, type);
    } else if (command == "MAX") {
      std::string type;
      std::cin >> type;
      kumekova::maxCommand(polygons, type);
    } else if (command == "MIN") {
      std::string type;
      std::cin >> type;
      kumekova::minCommand(polygons, type);
    } else if (command == "COUNT") {
      std::string type;
      std::cin >> type;
      kumekova::countCommand(polygons, type);
    } else if (command == "EXIT") {
      break;
    }
  }

  return 0;
}
