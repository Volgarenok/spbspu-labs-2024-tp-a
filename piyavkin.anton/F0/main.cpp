#include <iostream>
#include <functional>
#include <fstream>
#include <limits>
#include "commands.hpp"
#include "comlinearg.hpp"

int main(int argc, char* argv[])
{
  if (argc > 4)
  {
    std::cerr << "Not enough command line options\n";
    return 1;
  }
  using namespace piyavkin;
  dic_t dicts;
  if (argc != 1)
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Bad file\n";
      return 2;
    }
    std::map< std::string, std::function< void(std::ostream&) > > cmdLine;
    cmdLine["--help"] = help;
    cmdLine["--check"] = std::bind(check, std::ref(in), std::placeholders::_1, std::ref(dicts));
    size_t n = argc;
    try
    {
      for (size_t i = 2; i < n; ++i)
      {
        cmdLine.at(argv[i])(std::cout);
      }
      if (!in.eof())
      {
        input(in, dicts);
      }
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  std::map< std::string, std::function< void(std::istream&, const dic_t&) > > cmdsForOutput;
  cmdsForOutput["printdictionary"] = print;
  cmdsForOutput["topfreq"] = std::bind(topFreq, std::placeholders::_1, std::ref(std::cout), std::placeholders::_2);
  std::map< std::string, std::function< iterator(std::istream&, dic_t&) > > cmdsForCreate;
  cmdsForCreate["adddictionary"] = addDict;
  cmdsForCreate["changedictionary"] = cmdChange;
  cmdsForCreate["makedictionary"] = makeDict;
  cmdsForCreate["intersectdictionaries"] = intersect;
  cmdsForCreate["uniondictionaries"] = unionD;
  cmdsForCreate["uniquedictionaries"] = uniqueD;
  cmdsForCreate["adddictionarytodictionary"] = addDtoD;
  cmdsForCreate["subdictionarytodictionary"] = subD;
  std::string name = "";
  while (std::cin >> name)
  {
    try
    {
      cmdsForCreate.at(name)(std::cin, dicts);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        cmdsForOutput.at(name)(std::cin, dicts);
      }
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
