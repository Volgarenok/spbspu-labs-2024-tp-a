#include "dictionarymanager.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

int main()
{
  petuhov::DictionaryManager manager;
  std::string command;

  std::cout << "Commands:\n";
  std::cout << "CREATE <name> - Create a new dictionary\n";
  std::cout << "DELETE <name> - Delete an existing dictionary\n";
  std::cout << "INSERT <dict_name> <word> <translation> - Insert a word with its translation\n";
  std::cout << "REMOVE <dict_name> <word> - Remove a word from the dictionary\n";
  std::cout << "TRANSLATE <dict_name> <word> - Translate a word\n";
  std::cout << "MERGE <dict1> <dict2> - Merge two dictionaries\n";
  std::cout << "COMBINING <dict1> <dict2> - Show combined entries of two dictionaries\n";
  std::cout << "DIFFERENCE <dict1> <dict2> - Show the difference between two dictionaries\n";
  std::cout << "EXIT - Exit the program\n";

  while (std::cout << "> ", std::getline(std::cin, command))
  {
    std::istringstream iss(command);
    std::string cmd, dictName, dict2, word, translation;
    iss >> cmd;

    if (cmd == "CREATE")
    {
      iss >> dictName;
      manager.create(dictName);
    }
    else if (cmd == "DELETE")
    {
      iss >> dictName;
      manager.deleteDictionary(dictName);
    }
    else if (cmd == "INSERT")
    {
      if (!(iss >> dictName >> word >> translation))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.insert(dictName, word, translation);
    }
    else if (cmd == "REMOVE")
    {
      if (!(iss >> dictName >> word))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.remove(dictName, word);
    }
    else if (cmd == "TRANSLATE")
    {
      if (!(iss >> dictName >> word))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.translate(dictName, word);
    }
    else if (cmd == "MERGE")
    {
      if (!(iss >> dictName >> dict2))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.merge(dictName, dict2);
    }
    else if (cmd == "COMBINING")
    {
      if (!(iss >> dictName >> dict2))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.combining(dictName, dict2);
    }
    else if (cmd == "DIFFERENCE")
    {
      if (!(iss >> dictName >> dict2))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.difference(dictName, dict2);
    }
    else if (cmd == "EXIT")
    {
      break;
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }

  std::cout << "Goodbye!\n";
  return 0;
}
