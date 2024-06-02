#include <limits>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Commands.hpp"
#include "Utilites.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
     std::cout << "Required filename argument\n";
     return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.is_open())
  {
    std::cout << "File cannot be opened\n";
    return 2;
  }

  std::vector< erfurt::Dictionary > dictionaries = erfurt::createDictionaryFromFile(fin);

  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream & in) > > commands;
  commands["INSERT"] = std::bind(erfurt::makeInsert, _1, std::ref(dictionaries));
  commands["FINDTRANSLATE"] = std::bind(erfurt::makeFindTranslate, _1, std::ref(dictionaries), std::ref(std::cout));
  commands["DELETE"] = std::bind(erfurt::makeDelete, _1, std::ref(dictionaries));
  commands["PRINT"] = std::bind(erfurt::makePrint, _1, std::ref(dictionaries), std::ref(std::cout));
  commands["ISTRANSLATE"] = std::bind(erfurt::makeIsTranslate, _1, std::ref(dictionaries), std::ref(std::cout));
  commands["MERGE"] = std::bind(erfurt::makeMerge, _1, std::ref(dictionaries));
  commands["ADDCOMMON"] = std::bind(erfurt::makeCommon, _1, std::ref(dictionaries));
  commands["ADDUNIQUE"] = std::bind(erfurt::makeUnique, _1, std::ref(dictionaries));
  commands["ADDTRANSLATE"] = std::bind(erfurt::makeAddTranslate, _1, std::ref(dictionaries));
  commands["PRINTDICTIONARIES"] = std::bind(erfurt::makePrintDictionaries, std::ref(dictionaries), std::ref(std::cout));
  commands["SAVE"] = std::bind(erfurt::makeSave, _1, std::ref(dictionaries));
  commands["OPEN"] = std::bind(erfurt::makeOpen, _1, std::ref(dictionaries));
  commands["CREATEDICTIONARY"] = std::bind(erfurt::makeCreate, _1, std::ref(dictionaries));

  erfurt::makeHelp(std::cout);

  while (!std::cin.eof())
  {
    std::string command;
    if (std::cin >> command)
    {
      try
      {
        commands.at(command)(std::cin);
        std::cout << '\n';
      }
      catch (const std::out_of_range &)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      catch (const std::logic_error & e)
      {
        std::cout << e.what() << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
