#include <iostream>
#include <cstring>
#include <functional>
#include <limits>
#include "commands.hpp"
#include "commandStrategies.hpp"

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

  using Command = std::function< void(std::istream&) >;
  std::unordered_map< std::string, Command > commands;
  {
    using namespace std::placeholders;

    commands["insert"] = std::bind(insert, std::ref(storage), _1);
    commands["search"] = std::bind(search< KeyAndValueContain >, std::cref(storage), _1, std::ref(std::cout));
    commands["search-keys"] = std::bind(search< KeyContain >, std::cref(storage), _1, std::ref(std::cout));
    commands["search-values"] = std::bind(search< ValueContain >, std::cref(storage), _1, std::ref(std::cout));
    commands["remove"] = std::bind(remove< KeyAndValueEqual >, std::ref(storage), _1);
    commands["remove-keys"] = std::bind(remove< KeyEqual >, std::ref(storage), _1);
    commands["remove-values"] = std::bind(remove< ValueEqual >, std::ref(storage), _1);
    commands["create"] = std::bind(create, std::ref(storage), _1);
    commands["open"] = std::bind(open, std::ref(storage), _1);
    commands["save"] = std::bind(save, std::cref(storage), _1);
    commands["close"] = std::bind(close, std::ref(storage), _1);
    commands["print"] = std::bind(print, std::cref(storage), _1, std::ref(std::cout));
    commands["size"] = std::bind(size, std::cref(storage), _1, std::ref(std::cout));
    commands["merge"] = std::bind(merge, std::ref(storage), _1);
    commands["intersect"] = std::bind(intersect, std::ref(storage), _1);
    commands["filter"] = std::bind(filter, std::ref(storage), _1);
    commands["invert"] = std::bind(invert, std::ref(storage), _1);
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
      std::cout << "<INVALID_COMMAND>" << "\n";
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
