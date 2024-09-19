#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>
#include <functional>
#include <stdexcept>

#include "Geometry.h"
#include "Commands.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error argument\n";
    return EXIT_FAILURE;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Invalid file\n";
    return EXIT_FAILURE;
  }

  std::vector<serter::Polygon> data;
  while (true)
  {
    serter::Polygon poly;
    input >> poly;
    if (!input) break; // Okuma hatası durumunda döngüden çık
    data.push_back(poly);
  }

  std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;
  using namespace std::placeholders;
  commands["ECHO"] = std::bind(serter::echo, std::ref(data), _1, _2);
  commands["RMECHO"] = std::bind(serter::rmEcho, std::ref(data), _1, _2);
  commands["LESSAREA"] = std::bind(serter::lessArea, std::cref(data), _1, _2);

  while (true)
  {
    try
    {
      std::string command;
      std::cin >> command;
      if (commands.find(command) != commands.end())
      {
        commands.at(command)(std::cin, std::cout);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    catch (const std::runtime_error& e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
      break;
    }
  }

  return 0;
}

