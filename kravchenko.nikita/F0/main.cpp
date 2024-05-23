#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include "commands.hpp"

int main()
{
  using namespace kravchenko;
  DictionaryMap dicts;

  cmd::FreqArgs freqArgs;
  {
    using namespace std::placeholders;
    freqArgs["word"] = cmd::freqWord;
    freqArgs["least"] = std::bind(cmd::freqPred< std::less<> >, _1, _2, std::cref(dicts), std::less<>{});
    freqArgs["most"] = std::bind(cmd::freqPred< std::greater<> >, _1, _2, std::cref(dicts), std::greater<>{});
  }

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
    try
    {
      if (cmdsI.find(cmd) != cmdsI.cend())
      {
        cmdsI[cmd](std::cin);
      }
      else if (cmdsIO.find(cmd) != cmdsIO.cend())
      {
        cmdsIO[cmd](std::cin, std::cout);
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
