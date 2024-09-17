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

void sakovskaia::removeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName, word;
  input >> dictName >> word;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dict_t & dict = it->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>\n");
  }
  dict.erase(wordIt);
  int totalWords = dict.size();
  updateFrequencies(dict.begin(), dict.end(), totalWords);
  output << "<Word '" << word << "' removed and frequencies updated>\n";
}

void sakovskaia::frequencyCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName, word;
  input >> dictName >> word;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dict_t & dict = it->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>\n");
  }
  output << "Frequency of " << word << " in " << dictName << ": " << wordIt->second << "\n";
}

void sakovskaia::updateCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName, word;
  int newFrequency;
  input >> dictName >> word >> newFrequency;
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dict_t & dict = it->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>\n");
  }
  wordIt->second = newFrequency;
  int totalFrequency = calculateTotalFrequencyExcludeOne(dict.begin(), dict.end(), newFrequency);
  updateFrequenciesWithNew(dict.begin(), dict.end(), totalFrequency, newFrequency);
  output << "Frequency of " << word << " in " << dictName << " updated to " << newFrequency << ".\n";
}

void sakovskaia::combiningCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName1, dictName2, resultDictName;
  input >> dictName1 >> dictName2 >> resultDictName;
  auto dictIt1 = dicts.find(dictName1);
  auto dictIt2 = dicts.find(dictName2);
  if (dictIt1 == dicts.end() || dictIt2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dict_t & dict1 = dictIt1->second;
  dict_t & dict2 = dictIt2->second;
  if (dicts.find(resultDictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>\n");
  }
  dicts[resultDictName] = dict_t();
  dict_t & resultDict = dicts[resultDictName];
  int totalFrequency = calculateTotalFrequencyForTwo(dict1.begin(), dict1.end(), dict2.begin(), dict2.end());
  combineDictionaries(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), resultDict, totalFrequency);
  output << "Combined dictionaries successfully into " << resultDictName << ".\n";
}

void sakovskaia::diffCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName1, dictName2, resultDictName;
  input >> dictName1 >> dictName2 >> resultDictName;
  auto dictIt1 = dicts.find(dictName1);
  auto dictIt2 = dicts.find(dictName2);
  if (dictIt1 == dicts.end() || dictIt2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>\n");
  }
  dict_t &dict1 = dictIt1->second;
  dict_t &dict2 = dictIt2->second;
  if (dicts.find(resultDictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>\n");
  }
  dicts[resultDictName] = dict_t();
  dict_t &resultDict = dicts[resultDictName];
  int totalFrequency = calculateTotalFrequency(dict1.begin(), dict1.end());
  createDiffDictionary(dict1.begin(), dict1.end(), dict2, resultDict, totalFrequency);
  output << "Words unique to " << dictName1 << " saved in " << resultDictName << ".\n";
}
