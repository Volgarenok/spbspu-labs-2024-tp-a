#include <iostream>
#include <unordered_map>
#include <limits>
#include <functional>
#include <map>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include "commands.h"

using namespace kartamyshev;

int main(int argc, const char* argv[])
{
  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
  }
  DictionarySet dictionaries;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  using namespace std::placeholders;
  commands["help"] = std::bind(help, std::ref(std::cout));
  commands["create"] = std::bind(create, std::ref(dictionaries), _1);
  commands["insert"] = std::bind(insert, std::ref(dictionaries), _1);
  commands["fill_in"] = std::bind(fill_in, std::ref(dictionaries), _1);
  commands["list_information"] = std::bind(list_information, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["search"] = std::bind(search, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["delete_dictionary"] = std::bind(delete_dictionary, std::ref(dictionaries), _1);
  commands["merge"] = std::bind(merge, std::ref(dictionaries), _1);
  commands["get_merge"] = std::bind(get_merge, std::ref(dictionaries), _1);
  commands["list_popular"] = std::bind(list_popular, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["get_intersection"] = std::bind(get_intersection, std::ref(dictionaries), _1);
  commands["list_rare"] = std::bind(list_rare, std::ref(dictionaries), _1, std::ref(std::cout));
  commands["clear"] = std::bind(clear, std::ref(dictionaries), _1);
  commands["list_range_words"] = std::bind(list_range_words, std::ref(dictionaries), _1, std::ref(std::cout));

  std::string commandKey;
  std::cin >> commandKey;
  while (!std::cin.eof())
  {
    try
    {
      commands.at(commandKey)(std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> commandKey;
  }

  return 0;
}
