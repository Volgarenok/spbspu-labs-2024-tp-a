#include <iostream>
#include <fstream>
#include <map>
#include <functional>

#include "Dictionary.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    std::string fname = argv[1];
    std::ifstream file(fname);

    std::map< std::string, ayupov::ARDictionary > dictionaries;

    std::string nameDict;
    while (file >> nameDict)
    {
      file >> dictionaries[nameDict];
    }

    std::map < std::string, std::function< void(std::istream&, std::ostream&) > > commands;
    {
      using namespace std::placeholders;
    commands["--help"] = std::bind(ayupov::doHelp, _2);
    commands["create"] = std::bind(ayupov::doCreate, std::ref(dictionaries), _1);
    commands["insert"] = std::bind(ayupov::doInsert, std::ref(dictionaries), _1);
    commands["search"] = std::bind(ayupov::doSearch, std::ref(dictionaries), _1, _2);
    commands["print"] = std::bind(ayupov::doPrint, std::cref(dictionaries), _1, _2);
    commands["deleteWord"] = std::bind(ayupov::doDeleteWord, std::ref(dictionaries), _1);
    commands["deleteTranslation"] = std::bind(ayupov::doDeleteTranslation, std::ref(dictionaries), _1);
    commands["deleteDictionary"] = std::bind(ayupov::doDeleteDictionary, std::ref(dictionaries), _1);
    commands["same"] = std::bind(ayupov::doSame, std::ref(dictionaries), _1, _2);
    commands["merge"] = std::bind(ayupov::doMerge, std::ref(dictionaries), _1);
    commands["intersection"] = std::bind(ayupov::doIntersection, std::ref(dictionaries), _1);
    commands["size"] = std::bind(ayupov::doSize, std::ref(dictionaries), _1, _2);
    }

    std::string cmd;
    while (std::cin >> cmd)
    {
      try
      {
        commands.at(cmd)(std::cin, std::cout);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    file.close();
  }
  else
  {
    std::cerr << "not file" << "\n";
    return 1;
  }
  return 0;
}
