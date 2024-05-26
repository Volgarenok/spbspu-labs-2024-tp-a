#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <map>
#include "commands.hpp"
#include "inputDictionary.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  using dict = std::map< std::string, std::map< std::string, std::list< std::string > > >;
  dict dictionary;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    inputDictionary(file, dictionary);
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }
  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::list< std::string >&) > > commands;

  commands.push("print", std::bind(print, _1, std::cref(dictionary)));

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      std::list< std::string > args;
      inputArgs(std::cin, args);
      commands.at(command)(args);
      args.clear();
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "<INVALID INPUT>\n";
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
}
