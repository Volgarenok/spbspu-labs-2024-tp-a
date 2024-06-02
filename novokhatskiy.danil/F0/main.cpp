#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include <limits>
#include <random>
#include <functional>
#include <list>
#include <set>
#include "commands.hpp"
#include "dictionary.hpp"

using val_t = std::pair< std::string, std::set< std::string > >;
using dictionaries = std::map< std::string, novokhatskiy::Dictionary >;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }
  setlocale(LC_ALL, "Russian");
  using namespace novokhatskiy;
  dictionaries dictOfDicts;
  std::string inputCmd(argv[1]);
  if (inputCmd == "--help")
  {
    printHelp();
  }
  using namespace std::placeholders;
  std::random_device rand;
  std::map< std::string, std::function< void(dictionaries &, std::istream &) > >  commandsIn;
  std::map< std::string, std::function< void(dictionaries &, std::istream &, std::ostream &) > > commandsInOut;
  commandsInOut["print"] = print;
  commandsInOut["find"] = find;
  commandsIn["save"] = save;
  commandsIn["insert"] = insert;
  commandsIn["delete"] = deleteWord;
  commandsIn["random"] = std::bind(randomDict, _1, _2, std::ref(rand));
  commandsIn["unique"] = unique;
  commandsIn["merge"] = merge;
  commandsIn["search"] = search;
  commandsIn["edit"] = editTranslation;
  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      commandsIn.at(cmd)(dictOfDicts, std::cin);
    }
    catch (const std::out_of_range &)
    {
      try
      {
        commandsInOut.at(cmd)(dictOfDicts, std::cin, std::cout);
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
