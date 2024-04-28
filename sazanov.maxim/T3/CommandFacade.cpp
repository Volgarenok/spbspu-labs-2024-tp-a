#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include "Polygon.hpp"
#include "CommandFacade.hpp"

using namespace sazanov;
int main()
{
  std::vector< Polygon > polygons;
  using input_it_t = std::istream_iterator< Polygon >;
  while (!std::cin.fail())
  {
    std::copy(
      input_it_t{std::cin},
      input_it_t{},
      std::back_inserter(polygons)
    );
  }

  std::cin.clear();
  std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  CommandFacade facade(polygons, std::cin, std::cout);
  facade.nextCommand();

  return 0;
}
