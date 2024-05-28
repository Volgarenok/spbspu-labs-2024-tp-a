#include "commands.hpp"
#include <fstream>
#include <algorithm>
#include <functional>
#include "commandsImpl.hpp"

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

void baranov::printTopCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  auto pos = dicts.find(dictName);
  if (pos == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  dict_t tempdict = pos->second;
  size_t tmp = 0;
  if (in.peek() != '\n')
  {
    in >> tmp;
  }
  size_t count = tmp == 0 ? tempdict.size() : std::min(tmp, tempdict.size());
  if (count == 0)
  {
    return;
  }
  auto max = std::max_element(tempdict.cbegin(), tempdict.cend(), countComparator);
  out << max->first << ' ' << max->second;
  tempdict.erase(max);
  --count;
  for (size_t i = 0; i < count; ++i)
  {
    max = std::max_element(tempdict.cbegin(), tempdict.cend(), countComparator);
    out << '\n' << max->first << ' ' << max->second;
    tempdict.erase(max);
  }
}

void baranov::joinCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dict1Name;
  std::string dict2Name;
  in >> dict1Name;
  in >> dict2Name;
  auto pos1 = dicts.find(dict1Name);
  auto pos2 = dicts.find(dict2Name);
  if (pos1 == dicts.end() || pos2 == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  const dict_t & dict1 = pos1->second;
  const dict_t & dict2 = pos2->second;
  dict_t result = dict1;
  auto end = dict2.cend();
  for (auto i = dict2.cbegin(); i != end; ++i)
  {
    result[i->first] += i->second;
  }
  std::string resultDictName;
  in >> resultDictName;
  dicts[resultDictName] = result;
}

void baranov::intersectCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dict1Name;
  std::string dict2Name;
  in >> dict1Name;
  in >> dict2Name;
  auto pos1 = dicts.find(dict1Name);
  auto pos2 = dicts.find(dict2Name);
  if (pos1 == dicts.end() || pos2 == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  dict_t & dict1 = pos1->second;
  dict_t & dict2 = pos2->second;
  dict_t result;
  using namespace std::placeholders;
  auto predicate = std::bind(isContains, std::ref(dict2), _1);
  std::copy_if(dict1.cbegin(), dict1.cend(), std::inserter(result, result.begin()), predicate);
  auto end = result.end();
  for (auto i = result.begin(); i != end; ++i)
  {
    i->second += dict2.at(i->first);
  }
  std::string resultDictName;
  in >> resultDictName;
  dicts[resultDictName] = result;
}

void baranov::saveCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &)
{
  std::string dictName;
  in >> dictName;
  auto pos = dicts.find(dictName);
  if (pos == dicts.end())
  {
    throw std::logic_error("Invalid dictionary name\n");
  }
  std::string fileName;
  in >> fileName;
  std::ofstream file(fileName);
  file << dictName << '\n';
  dict_t & dict = pos->second;
  auto i = dict.cbegin();
  auto end = dict.cend();
  file << i->first << ' ' << i->second;
  ++i;
  for (; i != end; ++i)
  {
    file << '\n' << i->first << ' ' << i->second;
  }
}
