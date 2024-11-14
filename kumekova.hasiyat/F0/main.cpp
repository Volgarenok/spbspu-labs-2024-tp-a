#include "Commands.hpp"
#include "FrequencyDictionary.hpp"
#include <string>
#include <unordered_map>

using namespace kumekova;

void interactiveMode()
{
  std::unordered_map<std::string, FrequencyDictionary> dictionaries;
  std::string currentDictionary = "default";
  dictionaries[currentDictionary];

  std::cout << "Enter commands (type help for a list of commands):\n";

  while (true)
  {
    processCommand(dictionaries, currentDictionary);
  }
}

int main()
{
  interactiveMode();
  return 0;
}
