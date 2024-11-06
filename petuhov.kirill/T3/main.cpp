#include "polygon.hpp"
#include "polygonutils.hpp"
#include "commands.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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
      std::istringstream iss(line);
      std::string command;
      iss >> command;

      if (command == "SAME")
      {
        Polygon target;
        if (iss >> target)
        {
          int count = same_count(polygons, target);
          std::cout << "SAME " << count << std::endl;
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "PERMS")
      {
        Polygon target;
        if (iss >> target)
        {
          int count = perms_count(polygons, target);
          std::cout << "PERMS " << count << std::endl;
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (command == "RIGHTSHAPES")
      {
        int count = right_shapes_count(polygons);
        std::cout << "RIGHTSHAPES " << count << std::endl;
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
