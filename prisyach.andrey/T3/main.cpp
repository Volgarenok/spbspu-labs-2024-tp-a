#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <map>
#include <limits>
#include "geometric.hpp"
#include "calculations.hpp"
#include "streamguard.hpp"
#include "delimiters.hpp"

int main(int argc, char* argv[])
{
  using namespace prisyach;
  using namespace std::placeholders;
  if (argc != 2)
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }
  else
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Can not open file\n";
      return 1;
    }
    using input_iterator = std::istream_iterator< Polygon >;
    std::vector< Polygon > data;
    while (!in.eof())
    {
      std::copy(input_iterator{in}, input_iterator{}, std::back_inserter(data));
      if (in.fail())
      {
        in.clear();
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    std::map<std::string, std::function< void(std::istream &, std::ostream &) >> commands;
    commands["AREA"] = std::bind(doArea, std::cref(data), _1, _2);
    commands["MAX"] = std::bind(doMax, std::cref(data), _1, _2);
    commands["MIN"] = std::bind(doMin, std::cref(data), _1, _2);
    commands["COUNT"] = std::bind(doCount, std::cref(data), _1, _2);
    commands["PERMS"] = std::bind(doPerms, std::cref(data), _1, _2);
    commands["MAXSEQ"] = std::bind(doMaxSeq, std::cref(data), _1, _2);
    commands["RMECHO"] = std::bind(doRmEcho, std::ref(data), _1, _2);
    std::string command = "";
    while (std::cin >> command)
    {
      try
      {
        commands.at(command)(std::cin, std::cout);
        std::cout << "\n";
      }
      catch (const std::exception & e)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    in.close();
    return 0;
  }
}
