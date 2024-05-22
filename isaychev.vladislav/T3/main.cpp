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

  if (argc != 2)
  {
    std::cerr << "no file was provided\n";
    return 1;
  }

  polCollection figures;
  std::ifstream input(argv[1]);

  using iterI_t = std::istream_iterator< Polygon >;
  std::copy(iterI_t{input}, iterI_t{}, std::back_inserter(figures));

  using commonSignature = void(std::istream &, std::ostream &, polCollection &);
  std::map< std::string, std::function< commonSignature > > cmds;
  //while (!std::cin.eof()){}
}
