#include <exception>
#include <fstream>
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

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["scantext"] = std::bind(cmdScanText, _1, _2, std::ref(dicts));
    cmds["new"] = std::bind(cmdNew, _1, _2, std::ref(dicts));
    cmds["remove"] = std::bind(cmdRemove, _1, _2, std::ref(dicts));
    cmds["list"] = std::bind(cmdList, _2, std::cref(dicts));
    cmds["save"] = std::bind(cmdSave, _1, _2, std::cref(dicts));
    cmds["freq"] = std::bind(cmdFreq, _1, _2, std::cref(dicts), std::cref(freqArgs));
    cmds["intersect"] = std::bind(cmdSetOperation, _1, _2, std::ref(dicts), cmd::dictIntersect, "INTERSECT");
    cmds["union"] = std::bind(cmdSetOperation, _1, _2, std::ref(dicts), cmd::dictUnion, "UNION");
    cmds["difference"] = std::bind(cmdSetOperation, _1, _2, std::ref(dicts), cmd::dictDifference, "DIFFERENCE");
    cmds["complement"] = std::bind(cmdSetOperation, _1, _2, std::ref(dicts), cmd::dictComplement, "COMPLEMENT");
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range& e)
    {
      std::cout << "<INVALID COMMAND>\n";
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
