#include "commands.hpp"
#include <fstream>
#include "dictFunctions.hpp"

void baranov::createCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("Already exists\n");
  }
  dicts[dictName];
  if (in.peek() != '\n')
  {
    std::string fileName;
    in >> fileName;
    std::ifstream file(fileName);
    if (!file.is_open())
    {
      throw std::logic_error("Invalid file name\n");
    }
    extendDict(dicts[dictName], file);
  }
}

void baranov::clearCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  auto pos = dicts.find(dictName);
  if (pos == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  pos->second.clear();
}

void baranov::deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  auto pos = dicts.find(dictName);
  if (pos == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  dicts.erase(pos);
}

void baranov::addWordsCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  std::string fileName;
  in >> fileName;
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("Invalid file name\n");
  }
  extendDict(dicts[dictName], file);
}


