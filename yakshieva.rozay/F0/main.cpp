#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include "Command.hpp"
#include "WorkType.hpp"

void showHelp()
{
  std::cout << "  help                           - Show this help message\n";
  std::cout << "Available commands:\n";
  std::cout << "  new <dictName>                 - Create a new dictionary\n";
  std::cout << "  create <dictName> <fileName>   - Create a dictionary from a file\n";
  std::cout << "  addLine <dictName> <line>      - Add a line to the dictionary\n";
  std::cout << "  addWord <dictName> <word> <lineNumber> - Add a word to a specific line in the dictionary\n";
  std::cout << "  remove <dictName>              - Remove a dictionary\n";
  std::cout << "  search <dictName> <word>       - Search for a word in the dictionary\n";
  std::cout << "  showLine <dictName> <lineNumber> - Show a specific line from the dictionary\n";
  std::cout << "  erase <dictName> <lineNumber>  - Erase a specific line from the dictionary\n";
  std::cout << "  clear <dictName>               - Clear the dictionary\n";
  std::cout << "  print <dictName>               - Print the dictionary\n";
  std::cout << "  displayText <dictName>         - Display all text from the dictionary\n";
}

int main(int argc, char**)
{
  if (argc != 1)
  {
    std::cerr << "<INVALID_ARGUMENTS>\n";
    return 1;
  }
  yakshieva::tree_t dicts;
  using namespace std::placeholders;
  using func_t = std::function< void(std::string) >;
  std::map< std::string, func_t > commandsDict
  {
    { "--help", [](std::string) { showHelp(); } },
    { "new", std::bind(yakshieva::newTree, _1, std::ref(dicts)) },
    { "addLine", std::bind(yakshieva::addLine, _1, std::ref(dicts)) },
    { "addWord", std::bind(yakshieva::addWord, _1, std::ref(dicts)) },
    { "remove", std::bind(yakshieva::remove, _1, std::ref(dicts)) },
    { "search", std::bind(yakshieva::search, _1, std::ref(dicts), std::ref(std::cout)) },
    { "showLine", std::bind(yakshieva::showLine, _1, std::ref(dicts), std::ref(std::cout)) },
    { "erase", std::bind(yakshieva::erase, _1, std::ref(dicts)) },
    { "clear", std::bind(yakshieva::clear, _1, std::ref(dicts)) },
    { "print", std::bind(yakshieva::print, _1, std::ref(dicts), std::ref(std::cout)) },
    { "displayText", std::bind(yakshieva::displayText, _1, std::ref(dicts), std::ref(std::cout)) },
    { "create", std::bind(yakshieva::create, _1, std::ref(dicts)) },
  };
  while (std::cin)
  {
    std::string command{ "" };
    std::getline(std::cin, command);
    if (command.empty())
    {
      continue;
    }
    std::string commandName = yakshieva::getWord(command, false);
    std::map< std::string, func_t >::iterator commandsDictIter = commandsDict.find(commandName);
    try
    {
      if (commandsDictIter == commandsDict.end())
      {
        throw std::logic_error("<INVALID_COMMAND>");
      }
      commandsDictIter->second(command);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  return 0;
}
