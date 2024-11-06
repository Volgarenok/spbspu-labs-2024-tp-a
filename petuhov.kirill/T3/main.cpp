#include "polygon.hpp"
#include "polygonutils.hpp"
#include "commands.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

int main(int argc, char* argv[]) {
  using namespace petuhov;

  if (argc != 2) {
    std::cerr << "Using: ./program filename\n";
    return 1;
  }

  try {
    std::vector<Polygon> polygons = read_polygons(argv[1]);

    std::string line;
    while (std::getline(std::cin, line)) {
      std::istringstream iss(line);
      std::string command;
      iss >> command;

      if (command == "AREA") {
        std::string param;
        iss >> param;
        if (param == "EVEN") {
          std::cout << std::fixed << std::setprecision(1) << sum_area(polygons, true) << std::endl;
        } else if (param == "ODD") {
          std::cout << std::fixed << std::setprecision(1) << sum_area(polygons, false) << std::endl;
        } else if (param == "MEAN") {
          std::cout << std::fixed << std::setprecision(1) << mean_area(polygons) << std::endl;
        } else {
          int vertex_count = std::stoi(param);
          std::cout << std::fixed << std::setprecision(1) << sum_area_by_vertex_count(polygons, vertex_count) << std::endl;
        }
      } else if (command == "MAX") {
        std::string param;
        iss >> param;
        if (param == "AREA") {
          std::cout << std::fixed << std::setprecision(1) << max_area(polygons) << std::endl;
        } else if (param == "VERTEXES") {
          std::cout << max_vertex_count(polygons) << std::endl;
        }
      } else if (command == "MIN") {
        std::string param;
        iss >> param;
        if (param == "AREA") {
          std::cout << std::fixed << std::setprecision(1) << min_area(polygons) << std::endl;
        } else if (param == "VERTEXES") {
          std::cout << min_vertex_count(polygons) << std::endl;
        }
      } else if (command == "COUNT") {
        std::string param;
        iss >> param;
        if (param == "EVEN") {
          std::cout << count_by_vertex_parity(polygons, true) << std::endl;
        } else if (param == "ODD") {
          std::cout << count_by_vertex_parity(polygons, false) << std::endl;
        } else {
          int vertex_count = std::stoi(param);
          std::cout << count_by_vertex_count(polygons, vertex_count) << std::endl;
        }
      } else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
