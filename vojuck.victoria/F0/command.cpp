
#include <limits>
#include "command.hpp"

void vojuck::printHelp(std::ostream & output)
{
//1 2 3 4 5 6 7 8 9 10 11 12
  output << "1.Make new  dictionary:\n";
  output << "  make <dictionary_name>\n";
  output << "2.Delete dictionary:\n";
  output << "  delete <dictionary_name>\n";
  output << "3.Load words from file to the dictionary:\n";
  output << "  load <dictionary_name> <file_name>\n";
  output << "4.Add word to the dictionary:\n";
  output << "  add <dictionary_name> <word>\n";
  output << "5.Save dictionary to the file:\n";
  output << "  save <dictionary_name> <file_name>\n";
  output << "6.Remove word from the dictionary:\n";
  output << "  remove <dictionary_name> <word>\n";
  output << "7.Print frequency of the word in the dictionary:\n";
  output << "  count <dictionary_name> <word>\n";
  output << "8.print dictionary and their frequency";
  output << "  print <dictionary_name>\n";
  output << "9.Merge two dictionaries:\n";
  output << "  merge <dictionary_name1> <dictionary_name2> <total_name>\n";
  output << "10.Create a dictionary containing words and their frequencies\n";
  output << "  that are in the first and second dictionary,\n";
  output << "  but are missing words  that are in both:\n";
  output << "  merge_unique <dictionary_name1> <dictionary_name2> <total_name>\n";
  output << "11.Create a dictionary with intersection of two dictionary \n";
  output << "   intersection <dictionary_name1> <dictionary_name2>  <total_name>\n";
  output << "12.Print the word and its frequency, for the word with the minimum frequency.\n";
  output << "   min_freaq <dictionary_name1> <dictionary_name2> ... <dictionary_namen>\n";
  output << "13.Print the word and its frequency, for the word with the maximum frequency.\n";
  output << "   max_freaq <dictionary_name1> <dictionary_name2> ... <dictionary_namen>\n";
  output << "14.Print words whose frequency is greater than a given one.\n";
  output << "   more_freaq <dictionary_name1> <dictionary_name2> ... <dictionary_namen>\n";
  output << "15.Print words whose frequency is less than a given one.\n";
  output << "   less_freaq <dictionary_name1> <dictionary_name2> ... <dictionary_namen>\n";
}

void vojuck::updateFreq(dict_t::iterator it, dict_t::iterator end, int totalWords)
{
  if (totalWords == 0)
  {
    return;
  }
  while (it != end)
  {
    it->second = 1.0 / totalWords;
    ++it;
  }
}

void vojuck::increaseDict(dict_t & dict, std::istream & input)
{
  std::string word;
  while (input >> word)
  {
    std::string cleanWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
      char c = word[i];
      if (std::isalpha(c))
      {
        cleanWord += std::tolower(c);
      }
    }
    if (!cleanWord.empty())
    {
      dict[cleanWord]++;
    }
  }
}
//1
void vojuck::makeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
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
      throw std::logic_error("Couldn`t open file" + fileName + "\n");
    }
    vojuck::increaseDict(dicts[dictName], file);
  }
  output << "The dictionary " << dictName << " has been created.\n";
}
//5
void vojuck::saveDictToFile(std::ofstream & file, dict_t::const_iterator it, dict_t::const_iterator end)
{
  while (it != end)
  {
    file << it->first << " " << it->second << "\n";
    ++it;
  }
}
//2
void vojuck::deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
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

//3
void vojuck::loadCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  std::string fileName;
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
  increaseDict(dicts[dictName], file);
  output << "The dictionary " << dictName << " has been loaded.\n";
}
//4
void vojuck::addCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  std::string word;
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
//6
void vojuck::removeCmd(std::map< std::string, dict_t > & dicts, std::istream & input, std::ostream & output)
{
  std::string dictName;
  std::string word;
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
  vojuck::updateFreq(dict.begin(), dict.end(), totalWords);
  output << "Word '" << word << "' removed from " << dictName <<  " and frequencies updated.\n";
}
//7
void vojuck::wordFrequency(const std::map<std::string, dict_t>& dicts, std::istream & input, std::ostream& output)
{
  std::string dictName;
  std::string word;
  input >>  dictName >> word;
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    throw std::logic_error("<DICT NOT FOUND>\n");
  }

  const dict_t& dict = dictIt->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.end())
  {
     throw std::logic_error("<WORD NOT FOUND>\n");
  }

  output << "Frequency of word '" << word << "' in dictionary '" << dictName << "': " << wordIt->second << "\n";
}

//8
void vojuck::printDictionaryFrequencies(const std::map<std::string, dict_t>& dicts, std::ifstream &input, std::ostream & output)
{
  std::string dictName;
  input >> dictName;
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    throw std::logic_error("<DICT NOT FOUND>\n");
  }
  const dict_t& dict = dictIt->second;
  output << "Frequencies in dictionary '" << dictName << "': ";
  bool isFirst = true;
  for (const auto& entry : dict)
  {
    if (!isFirst)
    {
      output << " ";
    }
    output << entry.first << ": " << entry.second;
    isFirst = false;
  }
  output << "\n";
}

//9
void vojuck::mergeDict(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::string dictName1, dictName2, totalName;
  input >> dictName1 >> dictName2 >> totalName ;

  auto dictIt1 = dicts.find(dictName1);
  auto dictIt2 = dicts.find(dictName2);

  if (dictIt1 == dicts.end() || dictIt2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARIES NOT FOUND>\n");
  }
  const dict_t& dict1 = dictIt1->second;
  const dict_t& dict2 = dictIt2->second;

  dict_t mergedDict;

  for (const auto& entry : dict1)
  {
    mergedDict[entry.first] = entry.second;
  }

  for (const auto& entry : dict2)
  {
    if (mergedDict.find(entry.first) != mergedDict.end())
    {
    mergedDict[entry.first] += entry.second;
    }
    else
    {
      mergedDict[entry.first] = entry.second;
    }
  }
  dicts[totalName] = mergedDict;
  output << "Merged dictionary '" << totalName << "'has been created:\n";
}

//10
void vojuck::intersection(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::string dictName1, dictName2, totalName;
  input >> dictName1 >> dictName2 >> totalName;

  auto dictIt1 = dicts.find(dictName1);
  auto dictIt2 = dicts.find(dictName2);

  if (dictIt1 == dicts.end() || dictIt2 == dicts.end())
  {
    throw std::logic_error("<ONE OR BOTH DICTIONARIES NOT FOUND>\n");
  }

  const dict_t& dict1 = dictIt1->second;
  const dict_t& dict2 = dictIt2->second;

  dict_t intersectionDict;

  for (const auto& entry : dict1)
  {
    const std::string& word = entry.first;
    auto it2 = dict2.find(word);

    if (it2 != dict2.end())
    {
      intersectionDict[word] = std::min(entry.second, it2->second);
    }
  }
    dicts[totalName] = intersectionDict;
    output << "The intersection dictionary '" << totalName << "' has been created.\n";
}

//11
void vojuck::uniqueFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::string dictName1, dictName2, totalName;
  input >> dictName1 >> dictName2 >> totalName; // Считываем имена словарей

  auto dictIt1 = dicts.find(dictName1);
  auto dictIt2 = dicts.find(dictName2);

  if (dictIt1 == dicts.end() || dictIt2 == dicts.end())
  {
    throw std::logic_error("<ONE OR BOTH DICTIONARIES NOT FOUND>\n");
  }

  const dict_t& dict1 = dictIt1->second;
  const dict_t& dict2 = dictIt2->second;

  dict_t uniqueDict;

  for (const auto& entry : dict1)
  {
    if (dict2.find(entry.first) == dict2.end())
    {
      uniqueDict[entry.first] = entry.second;
    }
  }

  for (const auto& entry : dict2)
  {
    if (dict1.find(entry.first) == dict1.end())
    {
      uniqueDict[entry.first] = entry.second;
    }
  }
  dicts[totalName] = uniqueDict;
  output << "The unique frequency dictionary '" << totalName << "' has been created.\n";
}

//12
void vojuck::minFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::vector<std::string> dictNames;
  std::string dictName;
  while (input.peek() != '\n')
  {
    input >> dictName;
    dictNames.push_back(dictName);
  }

  if (dictNames.empty())
  {
     throw std::logic_error("<DICTIONARIES NOT FOUND>\n");
  }

  std::string minWord;
  int minFrequency = std::numeric_limits<int>::max();

  for (const auto& dictName : dictNames)
  {
    auto dictIt = dicts.find(dictName);
    if (dictIt == dicts.end())
    {
      continue;
    }

    const dict_t& dict = dictIt->second;
    for (const auto& entry : dict)
    {
      if (entry.second < minFrequency)
      {
        minFrequency = entry.second;
        minWord = entry.first;
      }
    }
  }

  if (!minWord.empty())
  {
    output << minWord << " " << minFrequency << "\n";
  }
  else
  {
    throw std::logic_error("<WORD NOT FOUND>\n");
  }
}

//13
void vojuck::maxFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::vector<std::string> dictNames;
  std::string dictName;
  while (input.peek() != '\n')
  {
    input >> dictName;
    dictNames.push_back(dictName);
  }

  if (dictNames.empty())
  {
     throw std::logic_error("<DICTIONARIES NOT FOUND>\n");
  }

  std::string maxWord;
  int maxFrequency = std::numeric_limits<int>::min();

  for (const auto& dictName : dictNames)
  {
    auto dictIt = dicts.find(dictName);
    if (dictIt == dicts.end())
    {
      continue;
    }

    const dict_t& dict = dictIt->second;
    for (const auto& entry : dict)
    {
      if (entry.second > maxFrequency)
      {
        maxFrequency = entry.second;
        maxWord = entry.first;
      }
    }
  }

  if (!maxWord.empty())
  {
    output << maxWord << maxFrequency << "\n";
  }
  else
  {
    throw std::logic_error("<WORD NOT FOUND>\n");
  }
}

//14
void vojuck::moreFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::vector<std::string> dictNames;
  std::string dictName;
  while (input >> dictName)
  {
    dictNames.push_back(dictName);
    if (input.peek() == '\n')
      break;
    }

  int number = 0;
  input >> number;

  if (dictNames.empty())
  {
    throw std::logic_error("<DICTIONARIES NOT FOUND>\n");
  }

  bool found = false;
  for (const auto& dictName : dictNames)
  {
    auto dictIt = dicts.find(dictName);
    if (dictIt == dicts.end())
    {
      continue;
    }

    const dict_t& dict = dictIt->second;

    for (const auto& entry : dict)
    {
      if (entry.second < number)
      {
        output << entry.first << ": " << entry.second << "\n";
        found = true;
      }
    }
  }

  if (!found)
  {
    output << "No words found with frequency less than " << number << ".\n";
  }
}

//15
void vojuck::lessFreq(std::map<std::string, dict_t>& dicts, std::istream& input, std::ostream& output)
{
  std::vector<std::string> dictNames;
  std::string dictName;
  while (input >> dictName)
  {
    dictNames.push_back(dictName);
    if (input.peek() == '\n')
      break;
    }

  int number = 0;
  input >> number;

  if (dictNames.empty())
  {
    throw std::logic_error("<DICTIONARIES NOT FOUND>\n");
  }

  bool found = false;
  for (const auto& dictName : dictNames)
  {
    auto dictIt = dicts.find(dictName);
    if (dictIt == dicts.end())
    {
      continue;
    }

    const dict_t& dict = dictIt->second;

    for (const auto& entry : dict)
    {
      if (entry.second > number)
      {
        output << entry.first << ": " << entry.second << "\n";
        found = true;
      }
    }
  }

  if (!found)
  {
    output << "No words found with frequency > than " << number << ".\n";
  }
}
