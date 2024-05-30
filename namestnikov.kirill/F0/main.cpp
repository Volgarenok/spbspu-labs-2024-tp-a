#include <iostream>
#include <fstream>
#include <unordered_map>
#include <limits>
#include <string>
#include <functional>
#include <delimeters.hpp>
#include "commands.hpp"
#include "input_output_data.hpp"

int main(int argc, char * argv[])
{
  using dictMain = std::unordered_map< std::string, std::unordered_map< std::string, std::string > >;
  using namespace namestnikov;
  dictMain myMap;
  try
  {
    for (int i = 1; i < argc; ++i)
    {
      if (std::string(argv[i]) == "--help")
      {
        doHelp(std::cout);
      }
      else
      {
        std::string filename = std::string(argv[i]) + ".txt";
        std::ifstream inFile(filename);
        if (!inFile.is_open())
        {
          std::cerr << "Cannot open file\n";
          return 1;
        }
        std::unordered_map< std::string, std::string > res = inputDict(inFile);
        myMap[argv[i]] = res;
      }
    }
  }
  catch (...)
  {
    std::cerr << "Error while trying to read dicts\n";
    return 1;
  }
  std::unordered_map< std::string, std::function< void(std::istream &) > > commands;
  {
    using namespace std::placeholders;
    commands["add"] = std::bind(doAdd, _1, std::ref(myMap), std::ref(std::cout));
    commands["find"] = std::bind(doFind, _1, std::ref(myMap), std::ref(std::cout));
    commands["postfix"] = std::bind(doPostfix, _1, std::ref(myMap), std::ref(std::cout));
    commands["remove"] = std::bind(doRemove, _1, std::ref(myMap), std::ref(std::cout));
    commands["subtract"] = std::bind(doSubtract, _1, std::ref(myMap), std::ref(std::cout));
    commands["merge"] = std::bind(doMerge, _1, std::ref(myMap), std::ref(std::cout));
    commands["export"] = std::bind(doExport, _1, std::cref(myMap));
    commands["palindrome"] = std::bind(doPalindrome, _1, std::ref(myMap), std::ref(std::cout));
    commands["import"] = std::bind(doImport, _1, std::ref(myMap));
    commands["prefix"] = std::bind(doPrefix, _1, std::ref(myMap), std::ref(std::cout));
    commands["create"] = std::bind(doCreate, _1, std::ref(myMap), std::ref(std::cout));
    commands["suffix"] = std::bind(doSuffix, _1, std::ref(myMap), std::ref(std::cout));
  }

  std::string commandName = "";
  while (std::cin >> commandName)
  {
    try
    {
      commands.at(commandName)(std::cin);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  try
  {
    for (const auto & pairDict: myMap)
    {
      std::ofstream outFile(pairDict.first + ".txt");
      outputDict(outFile, pairDict.second);
    }
  }
  catch (...)
  {
    std::cerr << "Error while trying to output dicts\n";
    return 1;
  }
}
