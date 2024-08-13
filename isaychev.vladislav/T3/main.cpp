#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <string>
#include "polygon.hpp"
#include "point.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
//  using namespace std::placeholders;

  collection_t figures;
  if (argc == 2)
  {
    using input_iter_t = std::istream_iterator< Polygon >;
    std::ifstream input(argv[1]);
    std::copy(input_iter_t{input}, input_iter_t{}, std::back_inserter(figures));
  }
  else
  {
    std::cerr << "wrong launch\n";
    return 1;
  }


  std::string str;
  std::cin >> str;
  try
  {
    do_count(std::cin, std::cout, figures);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
  }
  //std::map< std::string, std::function< void(std::istream &, std::ostream &, const collection &) > > m;
  //while (!std::cin.eof()){}
}
