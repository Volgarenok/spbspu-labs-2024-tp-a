#include "polygonutils.hpp"
#include "polygon.hpp"
#include "streamguard.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace petuhov
{
  std::vector<Polygon> read_polygons(const std::string &filename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      throw std::runtime_error("Error while opening file");
    }

    std::vector<Polygon> polygons;
    std::string line;

    while (std::getline(file, line))
    {
      Polygon polygon;
      size_t pos = 0;
      try
      {
        pos = line.find(' ');
        int num_vertices = std::stoi(line.substr(0, pos));
        size_t new_pos = pos + 1;

        for (int i = 0; i < num_vertices; ++i)
        {
          pos = line.find('(', new_pos);
          size_t semicolon_pos = line.find(';', pos + 1);
          size_t end_pos = line.find(')', semicolon_pos + 1);

          int x = std::stoi(line.substr(pos + 1, semicolon_pos - pos - 1));
          int y = std::stoi(line.substr(semicolon_pos + 1, end_pos - semicolon_pos - 1));

          polygon.points.push_back({x, y});
          new_pos = end_pos + 1;
        }
        polygons.push_back(polygon);
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << "\n";
      }
    }

    return polygons;
  }
}
