#include "polygon.hpp"
#include "polygonutils.hpp"
#include "commands.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int main(int argc, char *argv[])
{
  using namespace petuhov;

  if (argc != 2)
  {
    std::cerr << "Using: ./program filename\n";
    return 1;
  }

  try
  {
    std::vector<Polygon> polygons = read_polygons(argv[1]);

    std::string line;
    while (std::getline(std::cin, line))
    {
      size_t space_pos = line.find(' ');
      std::string command = line.substr(0, space_pos);
      std::string param = (space_pos != std::string::npos) ? line.substr(space_pos + 1) : "";

      if (command == "AREA")
      {
        if (param == "EVEN")
        {
          std::cout << std::fixed << std::setprecision(1) << sum_area(polygons, true) << "\n";
        }
        else if (param == "ODD")
        {
          std::cout << std::fixed << std::setprecision(1) << sum_area(polygons, false) << "\n";
        }
        else if (param == "MEAN")
        {
          std::cout << std::fixed << std::setprecision(1) << mean_area(polygons) << "\n";
        }
        else
        {
          try
          {
            int vertex_count = std::stoi(param);
            std::cout << std::fixed << std::setprecision(1) << sum_area_by_vertex_count(polygons, vertex_count) << "\n";
          }
          catch (const std::invalid_argument &)
          {
            std::cout << "<INVALID COMMAND>\n";
          }
        }
      }
      else if (command == "MAX")
      {
        if (param == "AREA")
        {
          std::cout << std::fixed << std::setprecision(1) << max_area(polygons) << "\n";
        }
        else if (param == "VERTEXES")
        {
          std::cout << max_vertex_count(polygons) << "\n";
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "MIN")
      {
        if (param == "AREA")
        {
          std::cout << std::fixed << std::setprecision(1) << min_area(polygons) << "\n";
        }
        else if (param == "VERTEXES")
        {
          std::cout << min_vertex_count(polygons) << "\n";
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "COUNT")
      {
        if (param == "EVEN")
        {
          std::cout << count_by_vertex_parity(polygons, true) << "\n";
        }
        else if (param == "ODD")
        {
          std::cout << count_by_vertex_parity(polygons, false) << "\n";
        }
        else
        {
          try
          {
            int vertex_count = std::stoi(param);
            std::cout << count_by_vertex_count(polygons, vertex_count) << "\n";
          }
          catch (const std::invalid_argument &)
          {
            std::cout << "<INVALID COMMAND>\n";
          }
        }
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Ошибка: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
