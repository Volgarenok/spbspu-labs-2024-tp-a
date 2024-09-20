#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include "commands.hpp"

int main()
{
  using namespace lebedev;
  std::map< std::string, Dictionary > dictionaries;
  std::map< std::string, std::function < void(dicts_t &, std::istream &, std::ostream &) > > commands;
  commands["readtext"] = getReadtextCmd;
  commands["find"] = getFindCmd;
  commands["delete"] = getDeleteCmd;
  commands["printtopn"] = getPrinttopnCmd;
  commands["printantitopn"] = getPrintantitopnCmd;
  commands["print"] = getPrintCmd;
  commands["merge"] = getMergeCmd;
  commands["union"] = getUnionCmd;
  commands["expand"] = getExpandCmd;
  commands["searchfreq"] = getSearchfreqCmd;
  //commands["save"] = getSaveCmd;
  //commands["readdict"] = getReaddictCmd;
  std::string curr_command;
  std::cin >> curr_command;
  while (!std::cin.eof())
  {
    if (curr_command == "--help")
    {
      doHelp(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    else
    {
      try
      {
        commands.at(curr_command)(dictionaries, std::cin, std::cout);
      }
      catch (const std::exception & e)
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        std::cout << e.what() << '\n';
      }
    }
    std::cin >> curr_command;
  }
}
