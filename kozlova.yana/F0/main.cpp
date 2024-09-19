#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <exception>
#include "dictionary.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace kozlova;
  std::map< std::string, Dictionary > dictionaries;
  std::map< std::string, std::function< void(std::map< std::string, Dictionary >&, std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["read"] = std::bind(read, _1, _2);
    cmds["readPart"] = std::bind(readPart, _1, _2);
    cmds["maxFreq"] = std::bind(findMaxFreq, _2, _3);
    cmds["combine"] = std::bind(combiningDictionary, _1, _2);
    cmds["remove"] = std::bind(removeWords, _1, _2);
    cmds["delete"] = std::bind(deleteDictionary, _1, _2);
    cmds["printFreq"] = std::bind(printFreqWord, _1, _2, _3);
    cmds["predecessor"] = std::bind(predecessor, _2, _3);
    cmds["print"] = std::bind(printDictCmd, _1, _2, _3);
  }

  while (!std::cin.eof())
  {
    std::string command;
    std::string str;
    if (std::cin >> command)
    {
      try
      {
        cmds.at(command)(dictionaries, std::cin, std::cout);
        std::cout << '\n';
      }
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      catch (const std::logic_error& e)
      {
        std::cout << e.what() << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
