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
  try
  {
    using cla_cmd_t = std::function< void(const std::string &, std::map< std::string, FreqList > &) >;
    std::map< std::string, cla_cmd_t > args;
    using namespace std::placeholders;
    args["--help"] = std::bind(print_help, std::ref(std::cout));
    args["--saved"] = load_saved;
    if (argc >= 2)
    {
      if (argc == 3)
      {
        args.at(argv[2])(argv[2], col);
      }
      args.at(argv[1])(argv[1], col);
    }
  }
  catch (const std::exception & e)
  {
    std::cout << e.what() << "\n";
    return 2;
  }
  if (!col.empty())
  {
    std::ofstream file("saved");
    for (auto i = col.begin(); i != col.end(); ++i)
    {
      file << (*i).first << ' ' << (*i).second.list.size() << '\n';
      file << (*i).second;
    }
  }
}
