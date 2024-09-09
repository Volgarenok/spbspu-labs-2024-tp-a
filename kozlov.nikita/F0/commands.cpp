#include "commands.hpp"
#include <algorithm>
#include <fstream>

void printEntry(const std::pair< const std::string, size_t >& entry, std::ostream& out);
void writeToFile(std::ofstream& file, const std::pair< const std::string, size_t >& entry);

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
  std::for_each(dict->second.begin(), dict->second.end(),
  std::bind(writeToFile, std::ref(file), std::placeholders::_1));
  out << "- Dictionary <" << dictName << "> saved to <" << path << ">.\n";
}

void kozlov::doCmdLoad(std::map<std::string, std::map<std::string, size_t>>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName, path;
  in >> dictName >> path;
  std::ifstream file(path);
  if (!file.is_open())
  {
    throw std::logic_error("<PATH NOT FOUND>");
  }
  std::map<std::string, size_t> newDict;
  std::string word;
  size_t count;
  while (file >> word >> count)
  {
    dict[word] = count;
  }
  dicts[dictName] = std::move(newDict);
  out << "- Dictionary <" << dictName << "> loaded from <" << path << ">.\n";
}
