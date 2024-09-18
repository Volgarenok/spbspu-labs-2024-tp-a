#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <map>

#include "commands.hpp"
#include "functions.hpp"

int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument\n";
    return 1;
  }

  std::string filename = argv[1];
  std::ifstream fin(filename);
  if (!fin.is_open())
  {
    std::cerr << "Error: invalid filename\n";
    return 2;
  }

  using namespace zaparin;

  Dicts dicts;
  loadFile(dicts["d0"], filename);
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

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

  commands["save"] = std::bind(save, std::ref(dicts), _1, _2);
  commands["load"] = std::bind(load, std::ref(dicts), _1, _2);

  commands["loadFile"] = std::bind(loadFile_cmd, std::ref(dicts), _1, _2);

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

