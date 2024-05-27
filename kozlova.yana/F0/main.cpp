#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "Commands.hpp"

int main()
{
  using namespace kozlova;
  std::map< std::string, std::map< std::string, size_t > > dictionaries;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["read"] = std::bind(read, std::ref(dictionaries), _1, _2);
    commands["readpart"] = std::bind(readPart, std::ref(dictionaries), _1, _2);
    commands["findmax"] = std::bind(findMaxFrequencyWord, std::ref(dictionaries), _1, _2);
    commands["findwith"] = std::bind(findFrequencyWordWith, std::ref(dictionaries), _1, _2);
    commands["print"] = std::bind(printFrequencyWord, std::ref(dictionaries), _1, _2);
    commands["deletedict"] = std::bind(deleteDictionary, std::ref(dictionaries), _1, _2);
    commands["deleteword"] = std::bind(deleteFrequencyWordWithPhrase, std::ref(dictionaries), _1, _2);
    commands["predecessor"] = std::bind(predecessor, std::ref(dictionaries), _1, _2);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
