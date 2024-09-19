#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <sstream>
#include <limits>
#include <locale>
#include <algorithm>
#include "command.h"

std::vector< std::string > split(const std::string& line)
{
  std::stringstream stream(line);
  std::string t;
  std::vector< std::string > vec;
  while (stream >> t)
  {
    vec.push_back(t);
  }
  return vec;
}

int main()
{
  using namespace basko;
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  std::map< std::string, std::map< std::string, std::set< int > > > maps;
  std::map<std::string,std::function<void(std::vector<std::string>&,std::map<std::string,std::map<std::string, std::set<int>>>&)>> commands;
  {
    using namespace std::placeholders;
    commands["createDict"] = std::bind(createDictCommand, _1, std::ref(maps));
    commands["add"] = std::bind(Addcommand, _1, std::ref(maps));
    commands["remove"] = std::bind(removeCommand, _1, std::ref(maps));
    commands["search"] = std::bind(searchCommand, _1, std::ref(maps));
    commands["show"] = std::bind(showCommand, _1, std::ref(maps));
    commands["top"] = std::bind(topCommand, _1, std::ref(maps));
    commands["merge"] = std::bind(mergeCommand, _1, std::ref(maps));
    commands["countwords"] = std::bind(countWordsCommand, _1, std::ref(maps));
    commands["clear"] = std::bind(clearCommand, _1, std::ref(maps));
    commands["matchWords"] = std::bind(matchWordsCommand, _1, std::ref(maps));
    commands["intersection"] = std::bind(intersectionCommand, _1, std::ref(maps));
    commands["help"] = std::bind(helpCommand, std::ref(std::cout));
  }
  std::string line;
  std::string command_name;
  std::cout << "Enter the command (-help) > ";
  while (std::getline(std::cin, line))
  {
    std::vector< std::string > words = split(line);
    if (words.empty())
    {
      std::cout << "INVALID COMMAND\n";
      std::cout << "Enter the command (-help) > ";
      continue;
    }
    command_name = words[0];
    if (command_name == "exit")
    {
      break;
    }
    try
    {
      auto command = commands.at(command_name);
      command(words, maps);
    }
    catch (const std::out_of_range& e)
    {
      std::cout << "INVALID COMMAND\n";
    }
    catch (const std::logic_error& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cout << "Enter the command (-help) > ";
  }
  return 0;
}
