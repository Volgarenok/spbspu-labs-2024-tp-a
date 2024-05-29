#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <functional>
#include "dictionary.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  using namespace nikitov;

  if (argc == 2)
  {
    if (std::string(argv[1]) == "--help")
    {
      std::cout << "1. print dictionary <dictName> - output of all words in the specified dictionary" << '\n'
        << "2. print all - output of all words from all dictionaries" << '\n'
        << "3. print names - output the names of all dictionaries" << '\n'
        << "4. find translation <dictName> <word> - search and output of a word translation from the dictionary" << '\n'
        << "5. find antonym <dictName> <word> - search and output of the word's antonyms from the dictionary" << '\n'
        << "6. translate sentence <dictName> - outputs a machine translation of a sentence based on the specified dictionary" << '\n'
        << "7. translate file <dictName> <inputFile> <outputFile> - reads text from a file and writes the translation to another file" << '\n'
        << "8. save dictionary <dictName> <newFileName> - saves the specified dictionary to a file" << '\n'
        << "9. create dictionary <dictName> - creates an empty dictionary with the specified name" << '\n'
        << "10. add translation <dictName> <word> <translation> - adds a word with a translation to the specified dictionary" << '\n'
        << "11. add antonym <dictName> <word> <antonym> - adds an antonym to the word" << '\n'
        << "12. edit primary <dictName> <word> - changes the main translation of the word" << '\n'
        << "13. edit secondary <dictName> <word> - changes the second translation of the word" << '\n'
        << "14. delete primary <dictName> <word> - delete the main translation of the word" << '\n'
        << "15. delete secondary <dictName> <word> - delete the second translation of the word" << '\n'
        << "16. delete antonym <dictName> <word> - remove the antonym of the word" << '\n';
    }
    return 0;
  }

  std::map< std::string, Dictionary > dictOfDicts;
  for (int i = 1; i != argc; ++i)
  {
    std::ifstream fileInput(argv[i]);
    if (fileInput)
    {
      Dictionary dict;
      fileInput >> dict;
      dictOfDicts.insert({ argv[i], dict });
    }
  }

  using namespace std::placeholders;
  std::map< std::pair< std::string, std::string >, std::function< void(const std::map< std::string, Dictionary >&,
    std::istream&, std::ostream&) > > constCommands;
  constCommands[{ "print", "dictionary" }] = printDictCmd;
  constCommands[{ "print", "all" }] = printAllCmd;
  constCommands[{ "print", "names" }] = printNamesCmd;
  constCommands[{ "find", "translation" }] = std::bind(findCmd, _1, _2, _3, "translation");
  constCommands[{ "find", "antonym" }] = std::bind(findCmd, _1, _2, _3, "antonym");
  constCommands[{ "translate", "sentence" }] = translateSentenceCmd;
  constCommands[{ "translate", "file" }] = translateFileCmd;
  constCommands[{ "save", "dictionary" }] = saveCmd;

  std::map< std::pair< std::string, std::string >, std::function< void(std::map< std::string, Dictionary >&, std::istream&) > > commands;
  commands[{ "create", "dictionary" }] = createCmd;
  commands[{ "add", "translation" }] = std::bind(addCmd, _1, _2, "translation");
  commands[{ "add", "antonym" }] = std::bind(addCmd, _1, _2, "antonym");
  commands[{ "edit", "primary" }] = std::bind(editCmd, _1, _2, "primary");
  commands[{ "edit", "secondary" }] = std::bind(editCmd, _1, _2, "secondary");
  commands[{ "delete", "primary" }] = std::bind(deleteCmd, _1, _2, "primary");
  commands[{ "delete", "secondary" }] = std::bind(deleteCmd, _1, _2, "secondary");
  commands[{ "delete", "antonym" }] = std::bind(deleteCmd, _1, _2, "antonym");


  std::string command;
  std::string parameter;
  while (std::cin >> command && std::cin >> parameter)
  {
    try
    {
      constCommands.at({ command, parameter })(dictOfDicts, std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        commands.at({ command, parameter })(dictOfDicts, std::cin);
      }
      catch (const std::out_of_range&)
      {
        std::cerr << "<INVALID COMMAND>" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
