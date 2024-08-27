#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <functional>
#include "commands.hpp"
#include "cla_cmd.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  if (argc > 3)
  {
    return 1;
  }
  std::map< std::string, FreqList > col;
  std::map< std::string, std::function< void(const std::string &, std::map< std::string, FreqList > &) > > args;
  using namespace std::placeholders;
  args["--help"] = std::bind(print_help, std::ref(std::cout));
  args["--saved"] = load_saved;
  try
  {
    if (argc >= 2)
    {
      if (argc == 3)
      {
        args.at(argv[2])(argv[2], col);
      }
      args.at(argv[1])(argv[2], col);
    }
  }
  catch (const std::exception & e)
  {
    std::cout << e.what() << "\n";
    return 2;
  }
}
