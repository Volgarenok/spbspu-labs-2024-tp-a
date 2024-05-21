#include <fstream>
#include <limits>
#include <map>
#include <exception>
#include "cmds.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  std::vector< Polygon > polygons;

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    using inputItT = std::istream_iterator< Polygon >;
    while (!infile.eof())
    {
      if (infile.fail())
      {
        infile.clear();
        infile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      std::copy(inputItT{ infile }, inputItT{}, std::back_inserter(polygons));
    }
  }

  int context = {};
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["CMD1"] = std::bind(cmd1, context, _2);
    cmds["CMD2"] = std::bind(cmd2, context, _2);
    cmds["CMD3"] = std::bind(cmd3, context, _2);
  }

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::overflow_error& e)
    {
      std::cerr << "<ERROR: " << e.what() << ">\n";
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
