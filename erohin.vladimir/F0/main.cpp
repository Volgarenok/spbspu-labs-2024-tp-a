#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <functional>
#include <limits>
#include "number_format.hpp"
#include "collection_commands.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  numformat_t used_numformat = NUMBER;
  if (argc == 3)
  {
    std::string format_arg(argv[1]);
    if (format_arg.substr(0, 12) == "--numformat=")
    {
      std::map< std::string, numformat_t > format;
      format["NUMBER"] = NUMBER;
      format["PROPORTION"] = PROPORTION;
      format["FRACTIONAL"] = FRACTIONAL;
      format["PERCENTAGE"] = PERCENTAGE;
      try
      {
        used_numformat = format.at(format_arg.substr(12));
      }
      catch (const std::out_of_range &)
      {
        std::cerr << "Wrong number format\n";
        return 1;
      }
    }
    else
    {
      std::cerr << "Wrong CLA to identify numformat\n";
      return 2;
    }
  }
  else if (argc != 2)
  {
    std::cerr << "Wrong CLA's number\n";
    return 3;
  }
  std::fstream file(argv[argc - 1]);
  collection context;

  context["test"]["word"] = 2;
  context["test"]["ya_word"] = 3;

  using command_func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, command_func > command;
  {
    using namespace std::placeholders;
    command["print"] = std::bind(print_command, std::ref(context), _1, _2, used_numformat);
  }
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  file.close();
  return 0;
}
