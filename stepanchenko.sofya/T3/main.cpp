#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include "Polygon.hpp"
#include "Commands.hpp"
#include "Utilities.hpp"


int main(int argc, char** argv)
{
  using namespace stepanchenko;
  if (argc < 2)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  std::ifstream input_file(argv[1]);
  if (!input_file)
  {
    std::cerr << "File doesn't exist\n";
    return 1;
  }
  std::vector< Polygon > figures;
  while (!input_file.eof())
  {
    std::copy(
    std::istream_iterator< Polygon >{input_file},
    std::istream_iterator< Polygon >{},
    std::back_inserter(figures)
    );

    if (!input_file && !input_file.eof())
    {
      input_file.clear();
      input_file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["AREA"] = std::bind(stepanchenko::areaCmd, figures, _1, _2);
  cmds["MAX"] = std::bind(stepanchenko::maxCmd, figures, _1, _2);
  cmds["MIN"] = std::bind(stepanchenko::minCmd, figures, _1, _2);
  cmds["COUNT"] = std::bind(stepanchenko::countCmd, figures, _1, _2);

  cmds["MAXSEQ"] = std::bind(stepanchenko::maxSeqCmd, figures, _1, _2);
  cmds["RMECHO"] = std::bind(stepanchenko::rmechoCmd, figures, _1, _2);
  cmds["INFRAME"] = std::bind(stepanchenko::inframeCmd, figures, _1, _2);

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
