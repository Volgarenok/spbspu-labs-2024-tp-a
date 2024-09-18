#include <iostream>
#include <fstream>
#include <map>
#include <functional>
#include "ERDictionary.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    if (std::string(argv[1]) == "--help")
    {
      std::cout << "1. insert <dictionary> <key> <value> - add a word with a translation" << '\n'
        << "2. search <dictionary> <key>  - output word translations" << '\n'
        << "3. delete <dictionary> <key>  - delete a word with all translations" << '\n'
        << "4. deletetranslation <dictionary> <key> <value> - delete a word translation" << '\n'
        << "5. searchshort <dictionary> <key> - output the shortest translation of a word" << '\n'
        << "6. searchsame <dictionary> <key> <key> - output identical translations of words" << '\n'
        << "7. identical <dictionary> <dictionary> - determine whether dictionaries consist of identical words" << '\n'
        << "8. combine <dictionary> <dictionary> - add the contents of the second dictionary to the first one" << '\n'
        << "9. intersection <dictionary> <dictionary> <name>> - create a new dictionary from common dictionary words" << '\n'
        << "10. save - saves all dictionaries to a file" << '\n';
      return 0;
    }

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
      commands["insert"] = std::bind(kozakova::insert, std::ref(dictionaries), _1);
      commands["search"] = std::bind(kozakova::search, std::cref(dictionaries), _1, _2);
      commands["delete"] = std::bind(kozakova::remove, std::ref(dictionaries), _1);
      commands["deletetranslation"] = std::bind(kozakova::removeTranslation, std::ref(dictionaries), _1);
      commands["searchshort"] = std::bind(kozakova::searchShort, std::cref(dictionaries), _1, _2);
      commands["searchsame"] = std::bind(kozakova::searchSame, std::cref(dictionaries), _1, _2);
      commands["identical"] = std::bind(kozakova::defineIdentical, std::cref(dictionaries), _1, _2);
      commands["combine"] = std::bind(kozakova::combine, std::ref(dictionaries), _1, _2);
      commands["intersection"] = std::bind(kozakova::getIntersection, std::ref(dictionaries), _1, _2);
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
