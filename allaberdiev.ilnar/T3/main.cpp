#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <streamGuard.hpp>
#include "commands.hpp"
#include "polygon.hpp"


int main(int argc, char** argv)
{
  using namespace allaberdiev;
  if (argc < 2)
  {
    std::cerr << "<NOT ENOUGH ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }

  std::vector< Polygon > polygons;

  using input_it = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it{file}, input_it{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  std::map< std::string, std::function< bool(const Polygon&) > > args;
  {
    using namespace std::placeholders;
    args["EVEN"] = std::bind(std::equal_to< double >{}, std::bind(std::modulus< size_t >{}, std::bind(get_size, _1), 2), 0);
    args["ODD"] = std::bind(std::not_equal_to< double >{}, std::bind(std::modulus< size_t >{}, std::bind(get_size, _1), 2), 0);
    args["MEAN"] = std::bind(std::equal_to< int >{}, 1, 1);
  }

  std::map< std::string, std::function< bool(const Polygon&) > > args_count;
  args_count["EVEN"] = args["EVEN"];
  args_count["ODD"] = args["ODD"];

  std::map< std::string, std::function< void(std::ostream&, std::istream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["COUNT"] = std::bind(count, _1, _2, std::cref(polygons), args_count);
    cmds["AREA"] = std::bind(getArea, _1, _2, std::cref(polygons), args);
    cmds["MAX"] = std::bind(findMax, _1, _2, std::cref(polygons));
    cmds["MIN"] = std::bind(findMin, _1, _2, std::cref(polygons));
    cmds["RMECHO"] = std::bind(rmEchoCommand, _1, _2, std::ref(polygons));
    cmds["RECTS"] = std::bind(rectsCommand, _1, std::ref(polygons));
    cmds["RIGHTSHAPES"] = std::bind(rightShapesCommand, _1, std::ref(polygons));
  }

  std::string command = "";
  while (std::cin >> command)
  {
    StreamGuard s_guard(std::cout);
    try
    {
      cmds.at(command)(std::cout, std::cin);
      std::cout << "\n";
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
