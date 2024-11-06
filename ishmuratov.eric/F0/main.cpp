#include <iostream>
#include <limits>
#include <functional>
#include <fstream>
#include <cstring>
#include <map>
#include "input.hpp"
#include "cmd.hpp"

int main(int argc, char * argv[])
{
  using namespace ishmuratov;

  dict_t dict;
  std::ifstream file;

  if (argc > 3)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  else if (argc > 1)
  {
    try
    {
      if (std::strcmp(argv[1], "--help") == 0)
      {
        print_help(std::cout);
      }
      else if (argc > 2 && std::strcmp(argv[2], "--help") == 0)
      {
        file.open(argv[1]);
        input_dictionary(dict, file);
        print_help(std::cout);
      }
      else if (argc == 2)
      {
        file.open(argv[1]);
        input_dictionary(dict, file);
      }
    }
    catch (...)
    {
      std::cerr << "Failed to read from file!\n";
      return 2;
    }
  }

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds.insert(std::make_pair("createdict", std::bind(create_dict, std::ref(dict), _1)));
    cmds.insert(std::make_pair("deletedict", std::bind(delete_dict, std::ref(dict), _1)));
    cmds.insert(std::make_pair("addkey", std::bind(add_key, std::ref(dict), _1)));
    cmds.insert(std::make_pair("addvalue", std::bind(add_value, std::ref(dict), _1)));
    cmds.insert(std::make_pair("removekey", std::bind(remove_key, std::ref(dict), _1)));
    cmds.insert(std::make_pair("printdict", std::bind(print_dict, std::ref(dict), _1, _2)));
    cmds.insert(std::make_pair("getvalue", std::bind(get_value, std::ref(dict), _1, _2)));
    cmds.insert(std::make_pair("save", std::bind(save, std::ref(dict), _1)));
    cmds.insert(std::make_pair("read", std::bind(read, std::ref(dict), _1)));
    cmds.insert(std::make_pair("rename", std::bind(renamedict, std::ref(dict), _1)));
    cmds.insert(std::make_pair("intersect", std::bind(intersect, std::ref(dict), _1)));
    cmds.insert(std::make_pair("union", std::bind(uniond, std::ref(dict), _1)));
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::underflow_error &)
    {
      std::cout << "<EMPTY>\n";
    }
    catch (const std::invalid_argument & e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
    catch (const std::runtime_error & e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
  }
  return 0;
}
