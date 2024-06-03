#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <map>
#include <set>
#include <functional>
#include "commands.hpp"
#include "inputDictionary.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  using dict = std::map< std::string, std::map< std::string, std::set< std::string > > >;
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

  commands["print"] = std::bind(print, _1, std::ref(std::cout), std::cref(dictionary));
  commands["intersect"] = std::bind(intersect, _1, std::ref(dictionary));
  commands["complement"] = std::bind(complement, _1, std::ref(dictionary));
  commands["union"] = std::bind(doUnion, _1, std::ref(dictionary));
  commands["specificLetter"] = std::bind(specificLetter, _1, std::ref(dictionary));
  commands["elimination"] = std::bind(elimination, _1, std::ref(dictionary));
  commands["destruction"] = std::bind(destruction, _1, std::ref(dictionary));
  commands["addition"] = std::bind(addition, _1, std::ref(dictionary));
  commands["palindrome"] = std::bind(palindrome, _1, std::ref(dictionary));
  commands["rider"] = std::bind(rider, _1, std::ref(dictionary));
  commands["interpreter"] = std::bind(interpreter, _1, std::ref(dictionary));
  commands["save"] = std::bind(save, _1, std::ref(dictionary));
  commands["addDictionary"] = std::bind(doAddDictionary, _1, std::ref(std::cin), std::ref(dictionary));

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      std::list< std::string > args;
      if (command != "addDictionary")
      {
        inputArgs(std::cin, args);
      }
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
