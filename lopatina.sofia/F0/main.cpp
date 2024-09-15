#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <exception>
#include "dictionary.hpp"
#include "commands.hpp"

int main(int argc, char ** argv)
{
  using namespace lopatina;

  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    doHelp(std::cout);
    return 0;
  }
  else if (argc == 3 && std::string(argv[1]) == "--check")
  {
    std::ifstream input(argv[2]);
    if (!input)
    {
      std::cout << "No such file\n";
    }
    else
    {
      std::cout << "Such file exist";
      if (input.peek() == std::ifstream::traits_type::eof())
      {
        std::cout << ", but it's empty";
      }
      std::cout << '\n';
    }
    return 0;
  }
  else if (argc != 1)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }

  std::map< std::string, Dictionary > dictionaries;
  std::map< std::string, std::function< void(std::map< std::string, Dictionary > &, std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["create"] = std::bind(createCmd, _1, _2);
    cmds["print"] = std::bind(printCmd, _1, _2, _3);
    cmds["sort"] = std::bind(sortCmd, _1, _2, _3);
    cmds["delete"] = std::bind(deleteCmd, _1, _2);
    cmds["compare"] = std::bind(compareCmd, _1, _2, _3);
    cmds["combine"] = std::bind(combineCmd, _1, _2);
    cmds["intersect"] = std::bind(intersectCmd, _1, _2);
    cmds["subtract"] = std::bind(subtractCmd, _1, _2);
    cmds["mostfrequent"] = std::bind(mostfrequentCmd, _1, _2, _3);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      std::string str;
      std::getline(std::cin, str);
      std::istringstream iss(str);
      if (cmds.find(cmd) != cmds.end())
      {
        cmds.at(cmd)(dictionaries, iss, std::cout);
      }
      else
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
    catch (const std::exception & e)
    {
      std::cout << e.what() << '\n';
    }
  }
  return 0;

}
