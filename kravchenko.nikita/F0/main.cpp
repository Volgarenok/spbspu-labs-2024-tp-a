#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include "commands.hpp"

int main()
{
  using namespace kravchenko;
  DictionaryMap dicts;

  std::map< std::string, std::function< void(std::istream&) > > cmdsI;
  {
    using namespace std::placeholders;
    cmdsI["SCANTEXT"] = std::bind(cmdScanText, _1, std::ref(dicts));
    cmdsI["NEW"] = std::bind(cmdNew, _1, std::ref(dicts));
    cmdsI["REMOVE"] = std::bind(cmdRemove, _1, std::ref(dicts));
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmdsIO;
  {
    using namespace std::placeholders;
    cmdsIO["LIST"] = std::bind(cmdList, _2, std::cref(dicts));
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    std::string line;
    std::getline(std::cin, line, '\n');
    std::stringstream cmdIn(line);
    try
    {
      if (cmdsI.find(cmd) != cmdsI.cend())
      {
        cmdsI[cmd](cmdIn);
      }
      else if (cmdsIO.find(cmd) != cmdsIO.cend())
      {
        cmdsIO[cmd](cmdIn, std::cout);
      }
      else
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}
