#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <string>
#include <functional>
#include "polygon.hpp"
#include "point.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  using namespace std::placeholders;

  if (argc != 2)
  {
    std::cerr << "no file was provided\n";
    return 1;
  }

  polCollection figures;
  std::ifstream input(argv[1]);

  using iterI_t = std::istream_iterator< Polygon >;
  std::copy(iterI_t{input}, iterI_t{}, std::back_inserter(figures));

  std::cout << getArea(figures[0]) << "\n";

  std::map< std::string, std::function< void(std::istream &, std::ostream &, const polCollection &) > > m;
  //while (!std::cin.eof()){}
}
