#include <iostream>
#include <unordered_map>
#include <sstream>
#include "FrequencyDictionaryCmds.hpp"

using namespace sazanov;

int main()
{
  DictionaryCollection dictionaries;
  Commands commands;
  commands["insert"] = std::bind(insert, std::ref(dictionaries), std::placeholders::_1, std::placeholders::_2);
  commands["get-frequency"] = std::bind(getFrequency, std::ref(dictionaries), std::placeholders::_1, std::placeholders::_2);
  commands["erase"] = std::bind(erase, std::ref(dictionaries), std::placeholders::_1, std::placeholders::_2);
  commands["get-most-frequent"] = std::bind(getMostFrequent, std::ref(dictionaries), std::placeholders::_1, std::placeholders::_2);
  commands["size"] = std::bind(size, std::ref(dictionaries), std::placeholders::_1, std::placeholders::_2);

  dictionaries["first"]["dog"] = 0;

  std::string line;
  std::string commandName;

  while (!std::cin.eof())
  {
    std::getline(std::cin, line, '\n');
    std::stringstream commandStream(line);
    commandStream >> commandName;
    if (commands.find(commandName) != commands.end())
    {
      commands[commandName](commandStream, std::cout);
    }
    else
    {
      std::cout << "INVALID COMMAND\n";
    }
  }

  return 0;
}
