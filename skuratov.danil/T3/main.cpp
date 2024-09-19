#include <fstream>
#include <exception>
#include <limits>
#include <map>
#include "cmds.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  std::vector< Polygon > poly;

  if (argc != 2)
  {
    std::cerr << "Error reading file" << '\n';
    return 1;
  }
  std::ifstream infile(argv[1]);

  using inputItT = std::istream_iterator< Polygon >;
  while (!infile.eof())
  {
    if (infile.fail())
    {
      infile.clear();
      infile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(inputItT{ infile }, inputItT{}, std::back_inserter(poly));
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(area, _1, _2, poly);
    cmds["MAX"] = std::bind(max, _1, _2, poly);
    cmds["MIN"] = std::bind(min, _1, _2, poly);
    cmds["COUNT"] = std::bind(count, _1, _2, poly);

    cmds["LESSAREA"] = std::bind(lessArea, _1, _2, poly);
    cmds["INFRAME"] = std::bind(inFrame, _1, _2, poly);
    cmds["RIGHTSHAPES"] = std::bind(rightShapes, _2, poly);
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
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
