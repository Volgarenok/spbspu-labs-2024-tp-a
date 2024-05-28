#include "secondary_commands.hpp"
#include <iostream>
#include <fstream>
#include "format.hpp"
#include "input_output_collection.hpp"

void erohin::printHelp(std::ostream & output)
{
  output << "\n";
}

void erohin::checkDictionary(const char * file_name, std::ostream & output)
{
  std::fstream file(file_name, std::ios::in);
  collection dict_context;
  std::string dict_name;
  file >> StringFormat{ dict_name, ':' };
  while (!file.eof())
  {
    if (file.fail())
    {
      break;
    }
    inputDictionary(dict_context[dict_name], file);
    if (!file)
    {
      file.clear();
    }
    file >> StringFormat{ dict_name, ':' };
  }
  file.close();
  output << "File contains " << (!file.eof() && file.fail() ? "incorrect" : "correct") << " frequency dictionaries.\n";
}
