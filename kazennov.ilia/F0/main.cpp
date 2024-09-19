#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <fstream>
#include <map>
#include <functional>
#include <vector>

#include "dictionary.h"
#include "commands.h"

int main(int argc, char* argv[])
{
  using namespace kazennov;
  std::map<std::string, FrequencyDict> mapOfDicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["ADD"] = std::bind(add_word, _1, std::ref(mapOfDicts));
    cmds["DELETE_WORD"] = std::bind(delete_word, _1, std::ref(mapOfDicts));
    cmds["DELETE_DICT"] = std::bind(delete_dictionary, _1, std::ref(mapOfDicts));
    cmds["FREQUENCY"] = std::bind(get_frequency, _1, _2, std::ref(mapOfDicts));
    cmds["GET_HIGHEST_FREQUENCY"] = std::bind(get_word_with_highest_frequency, _1, _2, std::ref(mapOfDicts));
    cmds["WORD_COUNT"] = std::bind(get_count_of_word, _1, _2, std::ref(mapOfDicts));
    cmds["OUTPUT"] = std::bind(output, _1, _2, std::ref(mapOfDicts));
    cmds["INTERSECTION"] = std::bind(intersection, _1, std::ref(mapOfDicts));
    cmds["FILE"] = std::bind(add_from_file, _1, std::ref(mapOfDicts));
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
