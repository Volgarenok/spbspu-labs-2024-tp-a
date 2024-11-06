#include <iostream>
#include <map>
#include <string>
#include <functional>

int main()
{
  using fun_t = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, fun_t > commands;

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
