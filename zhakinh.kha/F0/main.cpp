#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <stdexcept>
#include <limits>

#include "command.hpp"
#include "commandlineargs.hpp"

int main(int argc, char* argv[])
{
  using namespace zhakha;
  DictionaryMap dicts;

  if (argc > 4)
  {
    std::cerr << "Too many command line options\n";
    return 1;
  }

  if (argc > 1)
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Unable to open file\n";
      return 2;
    }

    std::map< std::string, std::function<void(std::ostream&)>> cmdLine;
    cmdLine["--help"] = help;
    cmdLine["--check"] = std::bind(check, std::ref(in), std::placeholders::_1, std::ref(dicts));


    size_t n = argc;
    try {
      for (size_t i = 2; i < n; ++i)
      {
        auto it = cmdLine.find(argv[i]);
        if (it != cmdLine.end())
        {
          it->second(std::cout);
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  std::map<std::string, std::function<void(std::istream&, const DictionaryMap&)>> cmdsForOutput;
  cmdsForOutput["printdictionary"] = print;
  cmdsForOutput["topfreq"] = std::bind(topFreq, std::placeholders::_1, std::ref(std::cout), std::placeholders::_2);

  std::map<std::string, std::function<DictionaryIterator(std::istream&, DictionaryMap&)>> cmdsForCreate;
  cmdsForCreate["adddictionary"] = addDict;
  cmdsForCreate["changedictionary"] = cmdChange;
  cmdsForCreate["makedictionary"] = makeDict;
  cmdsForCreate["intersectdictionaries"] = intersect;
  cmdsForCreate["uniondictionaries"] = unionD;
  cmdsForCreate["uniquedictionaries"] = uniqueD;
  cmdsForCreate["adddictionarytodictionary"] = addDtoD;
  cmdsForCreate["subdictionarytodictionary"] = subD;

  std::string command = "";

  while (std::cin >> command)
  {
    try
    {
      cmdsForCreate.at(command)(std::cin, dicts);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        cmdsForOutput.at(command)(std::cin, dicts);
      }
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}
