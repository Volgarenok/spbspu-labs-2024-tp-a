#include <functional>
#include <iostream>
#include <map>
#include <exception>

#include "commands.hpp"

int main()
{
  using namespace belokurskaya;
  std::vector< belokurskaya::EngRusDict > EngRusDicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["createDict"] = std::bind(cmd::createDict, std::ref(EngRusDicts), _1);
    commands["removeDict"] = std::bind(cmd::removeDict, std::ref(EngRusDicts), _1);
    commands["add"] = std::bind(cmd::add, std::ref(EngRusDicts), _1);
    commands["remove"] = std::bind(cmd::remove, std::ref(EngRusDicts), _1);
    commands["addWords"] = std::bind(cmd::addWords, std::ref(EngRusDicts), _1);
    commands["removeWords"] = std::bind(cmd::removeWords, std::ref(EngRusDicts), _1);
    commands["getIntersection"] = std::bind(cmd::getIntersection, std::ref(EngRusDicts), _1);
    commands["getDifference"] = std::bind(cmd::getDifference, std::ref(EngRusDicts), _1);
    commands["clear"] = std::bind(cmd::clear, std::ref(EngRusDicts), _1);
    commands["display"] = std::bind(cmd::display, std::ref(EngRusDicts), _1, _2);
    commands["getTranslation"] = std::bind(cmd::getTranslation, std::ref(EngRusDicts), _1, _2);
  }
  while (true)
  {
    std::string command;
    std::cin >> command;
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
