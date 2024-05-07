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

  dictionaries["first"]["dog"] = 0;

  std::string line;
  std::getline(std::cin, line, '\n');
  std::stringstream command(line);

  commands["insert"](command, std::cout);

  std::cout << dictionaries["first"]["cat"] << '\n';
  std::cout << dictionaries["first"]["dog"] << '\n';
  return 0;
}
