#include <iostream>
#include <map>
#include <functional>
#include <exception>
#include <limits>
#include <vector>
#include "dictionary.hpp"
#include "commands.hpp"

int main()
{
  using namespace grechishnikov;

  std::vector< Dictionary > dicts;
  std::map< std::string, std::function< void (const std::string&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["CREATE"] = std::bind(create, std::ref(dicts), _1);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      std::string param;
      std::getline(std::cin, param);
      cmds.at(cmd)(param);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  for (size_t i = 0; i < dicts.size(); i++)
  {
    std::cout << dicts[i].name_ << '\n';
  }
}
