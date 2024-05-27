#include <iostream>
#include <fstream>
#include <map>
#include <functional>
#include "ERDictionary.hpp"
#include "Commands.hpp"

#define NOMINMAX
#include "windows.h"

int main(int argc, char* argv[])
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  if (argc > 1)
  {
    std::string fname = argv[1];
    std::ifstream file(fname);

    std::map< std::string, kozakova::ERDictionary > dictionaries;

    std::string nameDict;
    while (file >> nameDict)
    {
      file >> dictionaries[nameDict];
    }

    std::map < std::string, std::function< void(std::istream&, std::ostream&) > > commands;
    {
      using namespace std::placeholders;
      commands["insert"] = std::bind(kozakova::insert, std::ref(dictionaries), _1, _2);
      commands["search"] = std::bind(kozakova::search, std::cref(dictionaries), _1, _2);
      commands["delete"] = std::bind(kozakova::remove, std::ref(dictionaries), _1, _2);
      commands["deletetranslation"] = std::bind(kozakova::removeTranslation, std::ref(dictionaries), _1, _2);
      commands["searchshort"] = std::bind(kozakova::searchShort, std::cref(dictionaries), _1, _2);
      commands["searchsame"] = std::bind(kozakova::searchSame, std::cref(dictionaries), _1, _2);
      commands["identical"] = std::bind(kozakova::identical, std::cref(dictionaries), _1, _2);
      commands["combine"] = std::bind(kozakova::combine, std::ref(dictionaries), _1, _2);
      commands["intersection"] = std::bind(kozakova::intersection, std::ref(dictionaries), _1, _2);
      commands["save"] = std::bind(kozakova::save, std::cref(dictionaries), fname);
    }

    std::string cmd;
    while (std::cin >> cmd)
    {
      try
      {
        commands.at(cmd)(std::cin, std::cout);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    file.close();
  }
  else
  {
    std::cerr << "not file" << "\n";
    return 1;
  }
  return 0;
}
