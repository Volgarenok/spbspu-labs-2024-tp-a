#include <iostream>
#include <map>
#include <limits>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <functional>

#include "polygon.hpp"
#include "commands.hpp"


int main(int argc, char* argv[])
{
  using namespace felk;
  if (argc != 2)
  {
    std::cerr << "Incorrect number\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  std::vector< Polygon > polys;
  while (!in.eof())
  {
    if (!in)
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(
      std::istream_iterator< Polygon >{in},
      std::istream_iterator< Polygon >{},
      std::back_inserter(polys)
    );
  }
  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  commands["AREA"] = std::bind(area, _1, _2, std::cref(polys));
  commands["COUNT"] = std::bind(count, _1, _2, std::cref(polys));
  commands["MAX"] = std::bind(max, _1, _2, std::cref(polys));
  commands["MIN"] = std::bind(min, _1, _2, std::cref(polys));
  commands["ECHO"] = std::bind(echo, _1, _2, std::ref(polys));
  commands["INFRAME"] = std::bind(inFrame, _1, _2, std::cref(polys));
  commands["MAXSEQ"] = std::bind(maxSeq, _1, _2, std::cref(polys));

  std::string cmd = "";
  std::cout << std::setprecision(1) << std::fixed;
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
