#include <iostream>
#include <cstring>
#include <functional>
#include <limits>
#include "commands.hpp"

int main(int argc, const char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Error: invalid arguments provided!\n";
    return 1;
  }

  if (argc == 2)
  {
    if (!std::strcmp(argv[1], "--help"))
    {
      std::cout << "Eng-Rus dictionary help\n";
      return 0;
    }
    else
    {
      std::cerr << "Error: invalid arguments provided!\n";
      return 1;
    }
  }

  using namespace novikov;
  DictionariesStorage storage;

  std::unordered_map< std::string, std::function< void(std::istream&) > > commands;
  {
    using namespace std::placeholders;

    commands["insert"] = std::bind(novikov::insert, std::ref(storage), _1);
    commands["search"] = std::bind(novikov::search, std::cref(storage), _1, std::ref(std::cout));
    commands["search-keys"] = std::bind(novikov::searchKeys, std::cref(storage), _1, std::ref(std::cout));
    commands["search-values"] = std::bind(novikov::searchValues, std::cref(storage), _1, std::ref(std::cout));
    /*
    commands["remove"] = novikov::remove;
    commands["remove-keys"] = novikov::removeKeys;
    commands["remove-values"] = novikov::removeValues;
    */
    commands["open"] = std::bind(novikov::open, std::ref(storage), _1);
    /*
    commands["save"] = novikov::save;
    */
    commands["close"] = std::bind(novikov::close, std::ref(storage), _1);
    commands["print"] = std::bind(novikov::print, std::cref(storage), _1, std::ref(std::cout));
    /*
    commands["print-reflected"] = novikov::printReflected;
    commands["size"] = novikov::size;
    commands["merge"] = novikov::merge;
    commands["intersect"] = novikov::intersect;
    commands["filter"] = novikov::filter;
    commands["invert"] = novikov::invert;
    */
  }

  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(std::cin);
    }
    catch (const std::logic_error& e)
    {
      std::cout << "<INVALID_COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}
