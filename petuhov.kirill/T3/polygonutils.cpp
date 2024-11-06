#include "polygonutils.hpp"
#include "polygon.hpp"
#include "streamguard.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace petuhov
{
  std::vector< Polygon > read_polygons(const std::string &filename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      throw std::runtime_error("Error while opening file");
    }

    std::vector< Polygon > polygons;
    Polygon polygon;
    std::string line;

    while (std::getline(file, line))
    {
      std::istringstream iss(line);
      StreamGuard guard(iss);
      if (iss >> polygon)
      {
        polygons.push_back(polygon);
      }
    }
    return polygons;
  }
}
