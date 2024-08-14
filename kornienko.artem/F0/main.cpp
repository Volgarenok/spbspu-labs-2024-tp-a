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

int main(int argc, char* argv[])
{
  using namespace kornienko;
  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    help(std::cout);
  }
  using mapDict = std::map< std::string, Dictionary >;
  mapDict dictionaries;
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["CREATE"] = std::bind(createDictionary, _1, _2, std::ref(dictionaries));
    cmds["DELETE"] = std::bind(deleteDictionary, _1, _2, std::ref(dictionaries));
    cmds["ADDWORD"] = std::bind(addWord, _1, _2, std::ref(dictionaries));
    cmds["DELETEWORD"] = std::bind(deleteWord, _1, _2, std::ref(dictionaries));
    cmds["ADDTRANSLATION"] = std::bind(addTranslation, _1, _2, std::ref(dictionaries));
    cmds["OUTPUT"] = std::bind(output, _1, _2, std::ref(dictionaries));
    cmds["MERGE"] = std::bind(merge, _1, _2, std::ref(dictionaries));
    cmds["INTERSECT"] = std::bind(intersect, _1, _2, std::ref(dictionaries));
    cmds["DIFFERENCE"] = std::bind(difference, _1, _2, std::ref(dictionaries));
    cmds["LIMIT"] = std::bind(limit, _1, _2, std::ref(dictionaries));
    cmds["GETTRANSLATION"] = std::bind(getTranslation, _1, _2, std::ref(dictionaries));
    cmds["NOTTRANSLATED"] = std::bind(notTranslated, _1, _2, std::ref(dictionaries));
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
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
