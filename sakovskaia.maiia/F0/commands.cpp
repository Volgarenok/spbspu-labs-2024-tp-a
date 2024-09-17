#include "commands.hpp"
#include <fstream>
#include <algorithm>
#include <functional>
#include "helping_commands.hpp"

void sakovskaia::newCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>\n");
  }
  dicts[dictName];
  if (in.peek() != '\n')
  {
    std::string fileName;
    input >> fileName;
    std::ifstream file(fileName);
    if (!file.is_open())
    {
      throw std::logic_error("Could not open file\n");
    }
    extendDict(dicts[dictName], file);
  }
}

void sakovskaia::deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  input >> dictName;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dicts.erase(it);
}

void sakovskaia::loadCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName, fileName;
  input >> dictName >> fileName;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("<FILE NOT FOUND>\n");
  }
  extendDict(dicts[dictName], file);
}

void sakovskaia::addCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName, word;
  input >> dictName >> word;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dict_t & dict = dicts[dictName];
  dict[word]++;
  output << "<" << word << " added to " << dictName << ">\n";
}

void sakovskaia::saveCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName, fileName;
  input >> dictName >> fileName;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("Could not open file for writing\n");
  }
  const dict_t & dict = dicts[dictName];
  auto start = dict.begin();
  auto end = dict.end();
  saveDictToFile(file, start, end);
  file.close();
}
