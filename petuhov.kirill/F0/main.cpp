#include "dictionary.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

int main()
{
  petuhov::Dictionary dictionary;
  std::string command;

  std::cout << "Commands:\n";
  std::cout << "INSERT <word> <translation> <additionalInfo>: Add a word with a translation and additional info\n";
  std::cout << "SEARCH <word>: Search for a word\n";
  std::cout << "DELETE <word>: Delete a word\n";
  std::cout << "EXIT: Exit the program\n";

  while (std::cout << "> ", std::getline(std::cin, command))
  {
    std::istringstream iss(command);
    std::string cmd, word, translation, additionalInfo;
    iss >> cmd;

    try
    {
      if (cmd == "INSERT")
      {
        if (!(iss >> word >> translation) || !std::getline(iss, additionalInfo))
        {
          std::cerr << "<INVALID COMMAND>\n";
          continue;
        }
        dictionary.insert(word, translation, additionalInfo);
      }
      else if (cmd == "SEARCH")
      {
        if (!(iss >> word))
        {
          std::cerr << "<INVALID COMMAND>\n";
          continue;
        }
        dictionary.search(word);
      }
      else if (cmd == "DELETE")
      {
        if (!(iss >> word))
        {
          std::cerr << "<INVALID COMMAND>\n";
          continue;
        }
        dictionary.remove(word);
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
    catch (const std::runtime_error &e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }

  std::cout << "Goodbye!\n";
  return 0;
}
