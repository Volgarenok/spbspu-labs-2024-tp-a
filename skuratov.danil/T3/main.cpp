#include <fstream>
#include <limits>
#include <map>
#include <exception>
#include "cmds.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  std::vector< Polygon > polygon;

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
      std::copy(inputItT{ infile }, inputItT{}, std::back_inserter(polygon));
    }
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(area, _1, _2, polygon);
    cmds["MAX"] = std::bind(max, _1, _2, polygon);
    cmds["MIN"] = std::bind(min, _1, _2, polygon);
    cmds["COUNT"] = std::bind(count, _1, _2, polygon);

    cmds["LESSAREA"] = std::bind(lessArea, _1, _2, polygon);
    cmds["INFRAME"] = std::bind(inFrame, _1, _2, polygon);
    cmds["RIGHTSHAPES"] = std::bind(rightShapes, _2, polygon);
  }

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
