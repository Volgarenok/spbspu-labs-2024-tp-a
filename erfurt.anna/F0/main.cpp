#include <limits>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Commands.hpp"
#include "Utilites.hpp"

namespace
{
  void makeIstreamClean(std::istream& in)
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  using mapCommandsType = std::map<std::string, std::function<void()>>;
  mapCommandsType defineAllCommands(std::istream & in, std::vector<erfurt::Dictionary> & base, std::ostream & out)
  {
    mapCommandsType mapOfCommands =
    {
      { "INSERT",std::bind(erfurt::makeInsert, std::ref(in), std::ref(base), std::ref(out))},
      { "FINDTRANSLATE",std::bind(erfurt::makeFindTranslate, std::ref(in), std::ref(base), std::ref(out)) },
      { "DELETE", std::bind(erfurt::makeDelete, std::ref(in), std::ref(base), std::ref(out)) },
      { "PRINT", std::bind(erfurt::makePrint, std::ref(in), std::ref(base), std::ref(out)) },
      { "ISTRANSLATE", std::bind(erfurt::makeIsTranslate, std::ref(in), std::ref(base), std::ref(out)) },
      { "MERGE", std::bind(erfurt::makeMerge, std::ref(in), std::ref(base), std::ref(out)) },
      { "ADDCOMMON", std::bind(erfurt::makeCommon, std::ref(in), std::ref(base), std::ref(out)) },
      { "ADDUNIQUE", std::bind(erfurt::makeUnique, std::ref(in), std::ref(base), std::ref(out)) },
      { "ADDTRANSLATE", std::bind(erfurt::makeAddTranslate, std::ref(in), std::ref(base), std::ref(out)) },
      { "HELP", std::bind(erfurt::makeHelp, std::ref(in), std::ref(base), std::ref(out)) },
      { "PRINTDICTIONARIES", std::bind(erfurt::makePrintDictionaries, std::ref(in), std::ref(base), std::ref(out)) },
      { "SAVE", std::bind(erfurt::makeSave, std::ref(in), std::ref(base), std::ref(out)) }
    };
    return mapOfCommands;
  }
}


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Required filename argument\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!file.is_open())
  {
    std::cout << "File cannot be opened\n";
    return 2;
  }
  std::vector<erfurt::Dictionary> dictionaries = erfurt::createDictionaryFromFile(fin);
  auto myCommands = defineAllCommands(std::cin, dictionaries, std::cout);
  std::cout << "\nDictionaries: ";
  erfurt::makePrintDictionaries(std::cin, dictionaries, std::cout);
  std::cout << '\n';
  std::cout << "Commands: " << '\n';
  for (const auto & cmd : myCommands)
  {
    std::cout << cmd.first << " ";
  }
  std::cout << '\n' << '\n' << "You can use HELP to get help about the command" << '\n' << '\n';
  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    if (!command.empty())
    {
      try
      {
        auto iter = myCommands.find(command);
        iter->second();
        std::cout << '\n';
      }
      catch (const std::logic_error& e)
      {
        std::cout << e.what() << '\n';
      }
      if ((std::cin.fail() && !std::cin.eof()) || myCommands.find(command) == myCommands.end())
      {
        makeIstreamClean(std::cin);
      }
    }
  }
  return 0;
}
