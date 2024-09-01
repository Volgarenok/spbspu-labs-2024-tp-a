#include <iostream>
#include <limits>
#include <fstream>
#include <iterator>
#include <functional>
#include "commands.hpp"
#include "cla_cmd.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  if (argc > 3)
  {
    std::cerr << "too many clas'\n";
    return 1;
  }

  std::map< std::string, FreqList > col;
  try
  {
    using cla_cmd_t = void(const std::string &, std::map< std::string, FreqList > &);
    std::map< std::string, std::function< cla_cmd_t > > args;
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
    std::cerr << e.what() << "\n";
    return 2;
  }

  using namespace std::placeholders;
  using command_t = void(std::istream &, std::ostream &);
  std::map< std::string, std::function< command_t > > cmd;

  cmd["makefreqlist"] = std::bind(make_freqlist, std::ref(col), _1);
  cmd["deletefreqlist"] = std::bind(delete_freqlist, std::ref(col), _1);
  cmd["mergelists"] = std::bind(merge, std::ref(col), _1);
  cmd["printlist"] = std::bind(print, std::cref(col), _1, _2);
  cmd["printlastnpos"] = std::bind(print_extremes, std::cref(col), std::cref("printlastnpos"), _1, _2);
  cmd["printfirstnpos"] = std::bind(print_extremes, std::cref(col), std::cref("printfirstnpos"), _1, _2);
  cmd["getcount"] = std::bind(count, std::cref(col), _1, _2);
  cmd["total"] = std::bind(get_total, std::cref(col), _1, _2);
  cmd["unique"] = std::bind(get_unique, std::cref(col), _1, _2);
  cmd["descending"] = std::bind(print_descending, std::cref(col), _1, _2);
  cmd["ls"] = std::bind(get_names, std::cref(col), _2);
  cmd["clear"] = std::bind(&collection_t::clear, &col);
  cmd["intersect"] = std::bind(intersect, std::ref(col), _1);

  std::string str;
  while (std::cin >> str)
  {
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      cmd.at(str)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID_COMMAND>\n";
    }
    catch (const std::exception & e)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << e.what() << "\n";
    }
  }

  if (!col.empty())
  {
    std::ofstream file("saved");
    for (auto i = col.begin(); i != col.end(); ++i)
    {
      file << (*i).first << ' ' << (*i).second.size() << '\n';
      file << (*i).second;
    }
  }
}
