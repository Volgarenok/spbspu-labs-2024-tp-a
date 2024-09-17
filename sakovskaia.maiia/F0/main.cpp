#include <iostream>
#include <map>
#include <string>
#include <functional>

int main(int argc, char * argv[])
{
  using namespace sakovskaia;
  std::map< std::string, std::map< std::string, size_t > > dictionaries;
  std::map< std::string, std::function< void(char **, std::ostream &) > > arguments;
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    arguments["--help"] = std::bind(printHelp, _2);
  }
  if (argc >= 2)
  {
    std::string argument = argv[1];
    try
    {
      arguments.at(argument)(argv, std::cout);
      return 0;
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>";
    }
  }
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  std::cin.clear();
  std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}
