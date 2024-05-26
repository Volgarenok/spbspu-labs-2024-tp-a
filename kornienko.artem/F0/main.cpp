#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <fstream>
#include <map>
#include <functional>
#include <vector>

#include "commands.hpp"
#include "dictionary.hpp"

int main()
{
  using namespace kornienko;
  using mapDict = std::map< std::string, Dictionary >;
  mapDict dictionaries;
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["CREATE"] = std::bind(createDictionary, _1, _2, std::ref(dictionaries));
    cmds["DELETE"] = std::bind(deleteDictionary, _1, _2, std::ref(dictionaries));
    cmds["ADDWORD"] = std::bind(addWord, _1, _2, std::ref(dictionaries));
    cmds["DELETEWORD"] = std::bind(deleteWord, _1, _2, std::ref(dictionaries));
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
      for (const auto& elem : dictionaries)
      {
        std::cout << elem.first << " words:\n";
        for (const auto& words : elem.second.dictionary_)
        {
          std::cout << words.first << " ";
        }
        std::cout << "\n";
      }
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error & e)
    {
      std::cout << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
