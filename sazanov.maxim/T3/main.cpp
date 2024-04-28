#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <fstream>
#include "Polygon.hpp"
#include "CommandFacade.hpp"

using namespace sazanov;
int main(int count, char* args[])
{
  if (count < 2)
  {
    std::cerr << "missed filename argument\n";
    return 1;
  }
  std::ifstream file(args[1]);
  if (!file.is_open())
  {
    std::cerr << "cant open file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(
      input_it_t{file},
      input_it_t{},
      std::back_inserter(polygons)
    );
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  CommandFacade facade(polygons, std::cin, std::cout);
  while (!std::cin.eof())
  {
    facade.nextCommand();
    std::cout << '\n';
  }
  return 0;
}
