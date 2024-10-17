#include "commands.hpp"
#include <algorithm>
#include <fstream>

void printEntry(const std::pair< const std::string, size_t >& entry, std::ostream& out);
void writeToFile(std::ofstream& file, const std::pair< const std::string, size_t >& entry);
void mergeWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry);
void intersectWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry, const std::map< std::string, size_t >& dict2);
void unionWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry);
void subtractWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry);

void kozlov::doCmdHelp(std::ostream& out)
{
  out << "Available commands:\n";

  out << "- create <name> - Сreate a new dictionary with the given <name>.\n";
  out << "- print <name> - Print the contents of the dictionary with the given <name>.\n";
  out << "- delete <name> - Delete the dictionary with the given <name>.\n";
  out << "- add <name> <word> - Add the <word> to the dictionary with the given <name>.\n";
  out << "- remove <name> <word> - Remove the <word> from the dictionary with the given <name>.\n";
  out << "- count <name> <word> - Display the count of the <word> in the dictionary with the given <name>.\n";
  out << "- save <name> <path> - Save the dictionary with the given <name> to a file at <path>.\n";
  out << "- load <name> <path> - Create a dictionary with the given <name> from the file at <path>.\n";
  out << "- merge <result> <dict1> <dict2> - Merge dictionaries <dict1> and <dict2> into a new dictionary <result>.\n";
  out << "- intersect <result> <dict1> <dict2> - Intersect dictionaries <dict1> and <dict2> into a new dictionary <result>.\n";
  out << "- union <result> <dict1> <dict2> - Union dictionaries <dict1> and <dict2> into a new dictionary <result>.\n";
  out << "- subtract <result> <dict1> <dict2> - Subtract dictionaries <dict1> and <dict2> into a new dictionary <result>.\n";
}

void kozlov::doCmdCreate(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  in >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }
  dicts[dictName] = {};
  out << "- Dictionary <" << dictName << "> created.\n";
}

void printEntry(const std::pair< const std::string, size_t >& entry, std::ostream& out)
{
  out << entry.first << ": " << entry.second << '\n';
}

void kozlov::doCmdPrint(std::map<std::string, std::map<std::string, size_t>>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  in >> dictName;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  if (dict->second.empty())
  {
    throw std::logic_error("<DICTIONARY IS EMPTY>");
  }
  std::for_each(dict->second.begin(), dict->second.end(), std::bind(printEntry, std::placeholders::_1, std::ref(out)));
}

void kozlov::doCmdDelete(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  in >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  dicts.erase(dictName);
  out << "- Dictionary <" << dictName << "> deleted.\n";
}

void kozlov::doCmdAdd(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  std::string word = "";
  in >> dictName >> word;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  auto& wordCount = dict->second[word];
  ++wordCount;
  out << "- Word <" << word << "> added to dictionary <" << dictName << ">.\n";
}

void kozlov::doCmdRemove(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  std::string word = "";
  in >> dictName >> word;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  auto dictWord = dict->second.find(word);
  if (dictWord == dict->second.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  if (dictWord->second > 1)
  {
    --dictWord->second;
  }
  else
  {
    dict->second.erase(dictWord);
  }
  out << "- Word <" << word << "> removed from dictionary <" << dictName << ">.\n";
}

void kozlov::doCmdCount(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  std::string word = "";
  in >> dictName >> word;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  auto dictWord = dict->second.find(word);
  if (dictWord == dict->second.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  out << dictWord->second << '\n';
}

void writeToFile(std::ofstream& file, const std::pair< const std::string, size_t >& entry)
{
  file << entry.first << " " << entry.second << "\n";
}

void kozlov::doCmdSave(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  std::string path = "";
  in >> dictName >> path;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::ofstream file(path);
  if (!file.is_open())
  {
    throw std::logic_error("<PATH NOT FOUND>");
  }
  std::for_each(dict->second.begin(), dict->second.end(), std::bind(writeToFile, std::ref(file), std::placeholders::_1));
  out << "- Dictionary <" << dictName << "> saved to <" << path << ">.\n";
}

void kozlov::doCmdLoad(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  std::string path = "";
  in >> dictName >> path;
  std::ifstream file(path);
  if (!file.is_open())
  {
    throw std::logic_error("<PATH NOT FOUND>");
  }
  std::map< std::string, size_t > newDict;
  std::string word = "";
  size_t count = 0;
  while (file >> word >> count)
  {
    newDict[word] = count;
  }
  dicts[dictName] = std::move(newDict);
  out << "- Dictionary <" << dictName << "> loaded from <" << path << ">.\n";
}

void mergeWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry)
{
  resultDict[entry.first] += entry.second;
}

void kozlov::doCmdMerge(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string result = "";
  std::string dict1Name = "";
  std::string dict2Name = "";
  in >> result >> dict1Name >> dict2Name;
  auto dict1 = dicts.find(dict1Name);
  auto dict2 = dicts.find(dict2Name);
  if (dict1 == dicts.end() || dict2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, size_t > mergedDict = dict1->second;
  std::for_each(dict2->second.begin(), dict2->second.end(), std::bind(mergeWord, std::ref(mergedDict), std::placeholders::_1));
  dicts[result] = std::move(mergedDict);
  out << "- Dictionary <" << result << "> created by merging <" << dict1Name << "> and <" << dict2Name << ">.\n";
}

void intersectWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry, const std::map< std::string, size_t >& dict2)
{
  auto dict = dict2.find(entry.first);
  if (dict != dict2.end())
  {
    resultDict[entry.first] = std::min(entry.second, dict->second);
  }
}

void kozlov::doCmdIntersect(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string result = "";
  std::string dict1Name = "";
  std::string dict2Name = "";
  in >> result >> dict1Name >> dict2Name;
  auto dict1 = dicts.find(dict1Name);
  auto dict2 = dicts.find(dict2Name);
  if (dict1 == dicts.end() || dict2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, size_t > intersectDict;
  std::for_each(dict1->second.begin(), dict1->second.end(), std::bind(intersectWord, std::ref(intersectDict), std::placeholders::_1, std::ref(dict2->second)));
  dicts[result] = std::move(intersectDict);
  out << "- Dictionary <" << result << "> created by intersecting <" << dict1Name << "> and <" << dict2Name << ">.\n";
}

void unionWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry)
{
  if (resultDict.find(entry.first) == resultDict.end())
  {
    resultDict[entry.first] = entry.second;
  }
}

void kozlov::doCmdUnion(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string result = "";
  std::string dict1Name = "";
  std::string dict2Name = "";
  in >> result >> dict1Name >> dict2Name;
  auto dict1 = dicts.find(dict1Name);
  auto dict2 = dicts.find(dict2Name);
  if (dict1 == dicts.end() || dict2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, size_t > unionDict = dict1->second;
  std::for_each(dict2->second.begin(), dict2->second.end(), std::bind(unionWord, std::ref(unionDict), std::placeholders::_1));
  dicts[result] = std::move(unionDict);
  out << "- Dictionary <" << result << "> created by union of <" << dict1Name << "> and <" << dict2Name << ">.\n";
}

void subtractWord(std::map< std::string, size_t >& resultDict, const std::pair< const std::string, size_t >& entry)
{
  auto dict = resultDict.find(entry.first);
  if (dict != resultDict.end())
  {
    if (dict->second > entry.second)
    {
      dict->second -= entry.second;
    }
    else
    {
       resultDict.erase(dict);
    }
  }
}

void kozlov::doCmdSubtract(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
  std::string result = "";
  std::string dict1Name = "";
  std::string dict2Name = "";
  in >> result >> dict1Name >> dict2Name;
  auto dict1 = dicts.find(dict1Name);
  auto dict2 = dicts.find(dict2Name);
  if (dict1 == dicts.end() || dict2 == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, size_t > subtractDict = dict1->second;
  std::for_each(dict2->second.begin(), dict2->second.end(), std::bind(subtractWord, std::ref(subtractDict), std::placeholders::_1));
  dicts[result] = std::move(subtractDict);
  out << "- Dictionary <" << result << "> created by subtracting <" << dict2Name << "> from <" << dict1Name << ">.\n";
}
