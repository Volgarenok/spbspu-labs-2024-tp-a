#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <limits>
#include <functional>
#include "commands.hpp"

int main(int argc, const char* argv[])
{
  using namespace kuznetsov;

  if (argc > 2)
  {
    std::cerr << "Error: invalid arguments provided!\n";
    return 0;
  }

  if (argc == 2)
  {
    if (!std::strcmp(argv[1], "--help"))
    {
      command_help(std::cout);
    }
    else if (!std::strcmp(argv[1], "--save"))
    {
      std::cout << "save\n";
    }
  }

  using frequency_dictionary = std::map< std::string, size_t >;

  std::map< std::string, frequency_dictionary > data;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["add_word"] = std::bind(command_add_word, std::ref(data), _1, _2);
    cmds["delete_word"] = std::bind(command_delete_word, std::ref(data), _1, _2);
    cmds["output"] = std::bind(command_output, std::ref(data), _1, _2);
    cmds["create_dictionary"] = std::bind(command_create_dictionary, std::ref(data), _1, _2);
    cmds["delete_dictionary"] = std::bind(command_delete_dictionary, std::ref(data), _1, _2);
    cmds["search_in_dictionary"] = std::bind(command_search_in_dictionary, std::ref(data), _1, _2);
    cmds["search_in_all_dictionary"] = std::bind(command_search_in_all_dictionary, std::ref(data), _1, _2);
    cmds["show_dictionary"] = std::bind(command_show_dictionary, std::ref(data), _2);
    cmds["add_words_from_file"] = std::bind(command_add_words_from_file, std::ref(data), _1, _2);
    cmds["merge"] = std::bind(command_merge, std::ref(data), _1, _2);
    cmds["intersection"] = std::bind(command_intersection, std::ref(data), _1, _2);
    cmds["top_popular_words"] = std::bind(command_merge, std::ref(data), _1, _2);
    cmds["create_dictionary_from_top_popular_words"] = std::bind(command_merge, std::ref(data), _1, _2);
    cmds["save"] = std::bind(command_save, std::ref(data), _2);
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
