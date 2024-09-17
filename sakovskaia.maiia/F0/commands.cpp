#include "commands.hpp"
#include "helping_commands.hpp"

void sakovskaia::printHelp(std::ostream & output)
{
  output << "1. Create new dictionary:\n";
  output << "   new <dictionary_name>\n";
  output << "2. Delete dictionary:\n";
  output << "   delete <dictionary_name>\n";
  output << "3. Load words from file to the dictionary:\n";
  output << "   load <dictionary_name> <file_name>\n";
  output << "4. Add word to the dictionary:\n";
  output << "   add <dictionary_name> <word>\n";
  output << "5. Save dictionary to the file:\n";
  output << "   save <dictionary_name> <file_name>\n";
  output << "6. Remove word from the dictionary:\n";
  output << "   remove <dictionary_name> <word>\n";
  output << "7. Print frequency of the word in the dictionary:\n";
  output << "   frequency <dictionary_name> <word>\n";
  output << "8. Update frequency of the word:\n";
  output << "   update <dictionary_name> <word> <new_frequency>\n";
  output << "9. Combine two dictionaries:\n";
  output << "   combining <dictionary_name1> <dictionary_name2> <result_name>\n";
  output << "10. Create a dictionary containing words and their frequencies\n";
  output << "   that are in the first dictionary, but are missing in the second:\n";
  output << "   diff <dictionary_name1> <dictionary_name2> <result_name>\n";
}

void sakovskaia::newCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>\n");
  }
  dicts[dictName];
  if (input.peek() != '\n')
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
  output << "The dictionary " << dictName << " has been created.\n";
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
  output << "The dictionary " << dictName << " has been deleted.\n";
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
  output << "The dictionary " << dictName << " has been loaded.\n";
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
  output << word << " added to " << dictName << ".\n";
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
  sakovskaia::saveDictToFile(file, start, end);
  file.close();
  output << "The dictionary " << dictName << " has been saved.\n";
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
  sakovskaia::updateFrequencies(dict.begin(), dict.end(), totalWords);
  output << "Word '" << word << "' removed and frequencies updated.\n";
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
  output << "Frequency of " << word << " in " << dictName << ": " << wordIt->second << ".\n";
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
  int totalFrequency = sakovskaia::calculateTotalFrequencyExcludeOne(dict.begin(), dict.end(), newFrequency);
  sakovskaia::updateFrequenciesWithNew(dict.begin(), dict.end(), totalFrequency, newFrequency);
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
  int totalFrequency = sakovskaia::calculateTotalFrequencyForTwo(dict1.begin(), dict1.end(), dict2.begin(), dict2.end());
  sakovskaia::combineDictionaries(dict1.begin(), dict1.end(), dict2.begin(), dict2.end(), resultDict, totalFrequency);
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
  dict_t & dict1 = dictIt1->second;
  dict_t & dict2 = dictIt2->second;
  if (dicts.find(resultDictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>\n");
  }
  dicts[resultDictName] = dict_t();
  dict_t & resultDict = dicts[resultDictName];
  int totalFrequency = sakovskaia::calculateTotalFrequency(dict1.begin(), dict1.end());
  sakovskaia::createDiffDictionary(dict1.begin(), dict1.end(), dict2, resultDict, totalFrequency);
  output << "Words unique to " << dictName1 << " saved in " << resultDictName << ".\n";
}
