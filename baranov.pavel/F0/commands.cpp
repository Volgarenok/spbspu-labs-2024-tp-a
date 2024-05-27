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

void baranov::printCountCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  if (in.peek() != '\n')
  {
    std::string dictName;
    in >> dictName;
    auto pos = dicts.find(dictName);
    if (pos == dicts.end())
    {
      throw std::logic_error("Invalid dictionary name\n");
    }
    dict_t & dict = pos->second;
    size_t count = 0;
    try
    {
      count = dict.at(word);
    }
    catch (const std::out_of_range &)
    {}
    out << count;
  }
  else
  {
    if (dicts.empty())
    {
      throw std::logic_error("There are no dictionaries\n");
    }
    auto i = dicts.cbegin();
    auto end = dicts.cend();
    size_t count = 0;
      try
      {
        count = i->second.at(word);
      }
      catch (const std::out_of_range &)
      {}
      out << i->first << ": " << count;
      ++i;
    for (; i != end; ++i)
    {
      count = 0;
      try
      {
        count = i->second.at(word);
      }
      catch (const std::out_of_range &)
      {}
      out << '\n' << i->first << ": " << count;
    }
  }
}

void baranov::printDictCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  auto pos = dicts.find(dictName);
  if (pos == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  dict_t & dict = pos->second;
  auto i = dict.cbegin();
  auto end = dict.cend();
  out << i->first << ' ' << i->second;
  ++i;
  for (; i != end; ++i)
  {
    out << '\n' << i->first << ' ' << i->second;
  }
}
