#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include "polygon.hpp"
#include "point.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;

  if (argc > 1)
  {
    std::vector< Polygon > figures;
    std::ifstream input(argv[1]);

    using iterI_t = std::istream_iterator< Polygon >;
    std::copy(iterI_t{input}, iterI_t{}, std::back_inserter(figures));

    using iterO_t = std::ostream_iterator< Polygon >;
    std::copy(figures.cbegin(), figures.cend(), iterO_t{std::cout, "\n"});
  }
  //while (!std::cin.eof()){}
}
