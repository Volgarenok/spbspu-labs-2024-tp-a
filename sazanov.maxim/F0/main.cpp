#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include "FrequencyDictionaryCmds.hpp"

using namespace sazanov;

int main()
{
  DictionaryCollection dictionaries;

  Commands commands;
  using namespace std::placeholders;
  commands["create"] = std::bind(create, std::ref(dictionaries), _1);
  commands["insert"] = std::bind(insert, std::ref(dictionaries), _1);
  commands["get-frequency"] = std::bind(getFrequency, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["erase"] = std::bind(erase, std::ref(dictionaries), _1);
  commands["get-most-frequent"] = std::bind(getMostFrequent, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["size"] = std::bind(size, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["read-text"] = std::bind(readText, std::ref(dictionaries), _1);
  commands["save"] = std::bind(save, std::ref(dictionaries), _1);
  commands["print"] = std::bind(print, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["read-dict"] = std::bind(readDict, std::ref(dictionaries), _1);
  commands["merge"] = std::bind(merge, std::ref(dictionaries), _1);
  commands["equal"] = std::bind(equal, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["intersect"] = std::bind(intersect, std::ref(dictionaries), _1);

  std::string line;
  std::string commandName;

  while (!std::cin.eof())
  {
    std::getline(std::cin, line, '\n');
    std::stringstream commandStream(line);
    commandStream >> commandName;
    try
    {
      commands.at(commandName)(commandStream);
    }
    catch (const std::exception&)
    {
      std::cout << "INVALID COMMAND\n";
    }
  }
  return 0;
}
