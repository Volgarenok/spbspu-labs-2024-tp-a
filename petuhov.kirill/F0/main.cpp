#include "dictionarymanager.hpp"
#include "streamguard.hpp"
#include <iostream>
#include <string>

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

  while (std::getline(std::cin, command))
  {
    size_t pos = 0;
    std::string cmd, dictName, dict2, word, translation;

    pos = command.find(' ');
    cmd = command.substr(0, pos);
    command.erase(0, pos + 1);

    petuhov::StreamGuard guard(std::cout);

    if (cmd == "CREATE")
    {
      dictName = command;
      manager.create(dictName);
    }
    else if (cmd == "DELETE")
    {
      dictName = command;
      manager.deleteDictionary(dictName);
    }
    else if (cmd == "INSERT")
    {
      pos = command.find(' ');
      dictName = command.substr(0, pos);
      command.erase(0, pos + 1);

      pos = command.find(' ');
      word = command.substr(0, pos);
      translation = command.substr(pos + 1);

      if (dictName.empty() || word.empty() || translation.empty())
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.insert(dictName, word, translation);
    }
    else if (cmd == "REMOVE")
    {
      pos = command.find(' ');
      dictName = command.substr(0, pos);
      word = command.substr(pos + 1);

      if (dictName.empty() || word.empty())
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.remove(dictName, word);
    }
    else if (cmd == "TRANSLATE")
    {
      pos = command.find(' ');
      dictName = command.substr(0, pos);
      word = command.substr(pos + 1);

      if (dictName.empty() || word.empty())
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.translate(dictName, word);
    }
    else if (cmd == "MERGE")
    {
      pos = command.find(' ');
      dictName = command.substr(0, pos);
      dict2 = command.substr(pos + 1);

      if (dictName.empty() || dict2.empty())
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.merge(dictName, dict2);
    }
    else if (cmd == "COMBINING")
    {
      pos = command.find(' ');
      dictName = command.substr(0, pos);
      dict2 = command.substr(pos + 1);

      if (dictName.empty() || dict2.empty())
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      manager.combining(dictName, dict2);
    }
    else if (cmd == "DIFFERENCE")
    {
      pos = command.find(' ');
      dictName = command.substr(0, pos);
      dict2 = command.substr(pos + 1);

      if (dictName.empty() || dict2.empty())
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
}
