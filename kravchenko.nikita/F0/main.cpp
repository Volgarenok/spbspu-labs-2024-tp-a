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

  cmd::FreqArgs freqArgs;
  freqArgs["word"] = cmd::freqWord;
  freqArgs["least"] = cmd::freqLeast;
  freqArgs["most"] = cmd::freqMost;

  std::map< std::string, std::function< void(std::istream&) > > cmdsI;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmdsIO;
  {
    using namespace std::placeholders;
    cmdsI["scantext"] = std::bind(cmdScanText, _1, std::ref(dicts));
    cmdsI["new"] = std::bind(cmdNew, _1, std::ref(dicts));
    cmdsI["remove"] = std::bind(cmdRemove, _1, std::ref(dicts));
    cmdsIO["list"] = std::bind(cmdList, _2, std::cref(dicts));
    cmdsIO["save"] = std::bind(cmdSave, _1, _2, std::cref(dicts));
    cmdsIO["freq"] = std::bind(cmdFreq, _1, _2, std::cref(dicts), std::cref(freqArgs));
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
