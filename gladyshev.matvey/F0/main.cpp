#include <iostream>
#include <limits>
#include <cstring>
#include <functional>

#include "commands.hpp"
#include "inputdata.hpp"

int main(int argc, char * argv[])
{
  using namespace gladyshev;
  using namespace std::placeholders;
  mainDic setDic;
  if (argc < 2)
  {
    std::cerr << "Bad data\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (argc == 3)
  {
    if (std::strcmp(argv[2], "--help") == 0)
    {
      printInfo(std::cout);
    }
    else
    {
      std::cerr << "Wrong argument\n";
      return 1;
    }
  }
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  cmds["addelem"] = std::bind(addelem, std::ref(setDic), _1);
  cmds["printdict"] = std::bind(print_dictionaries, std::cref(setDic), _1, _2);
  cmds["printgreater"] = std::bind(print_dictionariesL, std::cref(setDic), _1, _2);
  cmds["deleteName"] = std::bind(deleteName, std::ref(setDic), _1);
  cmds["deleteDict"] = std::bind(deleteDict, std::ref(setDic), _1);
  cmds["intersect"] = std::bind(intersect, std::ref(setDic), _1);
  cmds["addition"] = std::bind(addition, std::ref(setDic), _1);
  cmds["complement"] = std::bind(complement, std::ref(setDic), _1);
  cmds["makedict"] = std::bind(makeDict, std::ref(setDic), std::ref(file), _1);
  cmds["makedictlen"] = std::bind(makeDictLen, std::ref(setDic), std::ref(file), _1);
  cmds["save"] = std::bind(save, std::cref(setDic), _1);
  std::string command = "";
  while (!std::cin.eof())
  {
    std::cin >> command;
    try
    {
      cmds.at(command)(std::cin, std::cout);
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
