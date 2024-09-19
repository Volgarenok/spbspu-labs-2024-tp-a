#include <iostream>
#include <limits>
#include <functional>
#include <unordered_map>

#include "commands.hpp"

int main()
{
  using namespace felk;
  using namespace std::placeholders;
  std::unordered_map< std::string, Dict > collection;
  std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  commands["makedict"] = std::bind(makeDict, _1, _2, std::ref(collection));
  commands["split"] = std::bind(split, _1, _2, std::ref(collection));
  commands["setnewnumber"] = std::bind(setNewNumber, _1, _2, std::ref(collection));
  commands["getmean"] = std::bind(getMean, _1, _2, std::ref(collection));
  commands["deletekey"] = std::bind(deleteKey, _1, _2, std::ref(collection));
  commands["clear"] = std::bind(clear, _1, _2, std::ref(collection));
  commands["filter"] = std::bind(filter, _1, _2, std::ref(collection));
  commands["print"] = std::bind(print, _1, _2, std::ref(collection));
  commands["getunique"] = std::bind(getUnique, _1, _2, std::ref(collection));
  commands["lenfilter"] = std::bind(lenFilter, _1, _2, std::ref(collection));

  std::string command = "";
  while (!std::cin.eof())
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << e.what() << "\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
    }
  }
}
