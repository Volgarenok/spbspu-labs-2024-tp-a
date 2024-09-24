#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <map>
#include <limits>
#include "cmd.hpp"
#include "input.hpp"

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  using namespace sivkov;
  using mapType = std::map<std::string, std::map<std::string, std::string>>;
  mapType treeOfdic;

  if (argc != 2)
  {
    std::cerr << "Command line error\n";
    return 1;
  }

  if (std::string(argv[1]) == "help")
  {
    help(std::cout);
    return 0;
  }
  else
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
    treeOfdic = inputDictionary(file);
  }

  std::string command;

  using funcForPrint = std::function< void(mapType&, std::istream&, std::ostream&) >;
  std::map< std::string, funcForPrint > outCommands;
  outCommands["list_words"] = list_words;
  outCommands["search_words"] = search_words;
  outCommands["repeating_words"] = repeating_words;
  outCommands["count"] = count_words;

  using func = std::function< void(mapType&, std::istream&) >;
  std::map< std::string, func > cmd;
  cmd["add_word"] = add_word;
  cmd["add_translation"] = add_translation;
  cmd["create"] = create_dictionary;
  cmd["remove_word"] = remove_word;
  cmd["delete_dictionary"] = delete_dictionary;
  cmd["rename_dictionary"] = rename_dictionary;
  cmd["merge"] = merge_dictionaries;

  std::string inputCommand = "";

  while (std::cin >> inputCommand)
  {
    try
    {
      auto it = cmd.find(inputCommand);
      if (it != cmd.cend())
      {
        it->second(treeOfdic, std::cin);
      }
      else
      {
        auto itPrint = outCommands.find(inputCommand);
        if (itPrint != outCommands.cend())
        {
          itPrint->second(treeOfdic, std::cin, std::cout);
        }
        else
        {
          throw std::out_of_range("Invalid command");
        }
      }
    }
    catch (const std::out_of_range& e)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  try
  {
    save(treeOfdic, argv[1]);
  }
  catch (const std::logic_error& e)
  {
    std::cerr << "Error saving file: " << e.what() << "\n";
  }
  return 0;
}

