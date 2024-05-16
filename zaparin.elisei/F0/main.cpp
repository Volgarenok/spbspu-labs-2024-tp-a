#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <limits>
#include <map>

#include "Hash.hpp"
#include "Commands.hpp"

int main()
{
  std::map< std::string, zaparin::HashTable > dicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

  using namespace zaparin;
  using namespace std::placeholders;
  commands["createDict"] = std::bind(createDict, std::ref(dicts), _1, _2);
  commands["addWord"] = std::bind(addWord, std::ref(dicts), _1, _2);
  commands["getWordRate"] = std::bind(getWordRate, std::ref(dicts), _1, _2);
  commands["removeWord"] = std::bind(removeWord, std::ref(dicts), _1, _2);
  commands["deleteWord"] = std::bind(deleteWord, std::ref(dicts), _1, _2);
  commands["getAllWordsRate"] = std::bind(getAllWordsRate, std::ref(dicts), _1, _2);
  commands["getHighestRateWord"] = std::bind(getHighestRateWord, std::ref(dicts), _1, _2);
  commands["getLowestRateWord"] = std::bind(getLowestRateWord, std::ref(dicts), _1, _2);
  commands["getWordsWithRate"] = std::bind(getWordsWithRate, std::ref(dicts), _1, _2);
  commands["mergeDicts"] = std::bind(mergeDicts, std::ref(dicts), _1, _2);
  commands["intersectDicts"] = std::bind(intersectDicts, std::ref(dicts), _1, _2);
  commands["excluseDicts"] = std::bind(excluseDicts, std::ref(dicts), _1, _2);
  commands["getThreeHighestRateWords"] = std::bind(getThreeHighestRateWords, std::ref(dicts), _1, _2);
  commands["loadFile"] = std::bind(loadFile, std::ref(dicts), _1, _2);

  commands["save"] = std::bind(save, std::ref(dicts), _1, _2);
  commands["load"] = std::bind(load, std::ref(dicts), _1, _2);

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}