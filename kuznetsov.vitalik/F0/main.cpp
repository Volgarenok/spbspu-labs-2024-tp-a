#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <limits>
#include <functional>
#include "commands.hpp"

int main()
{
  using namespace kuznetsov;

  using frequency_dictionary = std::map< std::string, size_t >;

  std::map< std::string, frequency_dictionary > data;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["add_word"] = std::bind(command_add_word, std::ref(data), _1, _2);
    cmds["create_dictionary"] = std::bind(command_create_dictionary, std::ref(data), _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID_COMMAND>" << "\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
