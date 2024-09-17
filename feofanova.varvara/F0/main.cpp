#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include "commands.hpp"

using namespace feofanova;
int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 1;
  }
  std::string arg(argv[1]);
  std::map< std::string, std::map< std::string, size_t > > dictionaries = {};

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["Add_eng_rus"] = std::bind(CreateER, std::ref(dictionaries), _1, _2);
  cmds["Add_rus_eng"] = std::bind(CreateRE, std::ref(dictionaries), _1, _2);
  cmds["Find_eng_rus"] = std::bind(FindER, std::ref(dictionaries), _1, _2);
  cmds["Find_rus_eng"] = std::bind(FindRE, std::ref(dictionaries), _1, _2);
  cmds["Delete_eng_rus"] = std::bind(DeleteER, std::ref(dictionaries), _1, _2);
  cmds["Delete_rus_eng"] = std::bind(DeleteRE, std::ref(dictionaries), _1, _2);
  cmds["Flip"] = std::bind(doFlip, std::ref(dictionaries), _1, _2);
  cmds["Filter"] = std::bind(doFilter, std::ref(dictionaries), _1, _2);
  cmds["Compare_full"] = std::bind(FullCompare, std::ref(dictionaries), _1, _2);
  cmds["Compare_part"] = std::bind(PartCompare, std::ref(dictionaries), _1, _2);
  cmds["Unite"] = std::bind(doUnion, std::ref(dictionaries), _1, _2);
  cmds["Cross"] = std::bind(doCross, std::ref(dictionaries), _1, _2);
  cmds["Extend"] = std::bind(doExtend, std::ref(dictionaries), _1, _2);
  cmds["Reduce"] = std::bind(doReduce, std::ref(dictionaries), _1, _2);
  cmds["Print_all"] = std::bind(FullPrint, std::ref(dictionaries), _1, _2);
  cmds["Print"] = std::bind(PartPrint, std::ref(dictionaries), _1, _2);

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
