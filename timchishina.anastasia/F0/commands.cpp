#include "commands.hpp"
#include <algorithm>
#include <functional>

void printPosition(int position, std::ostream& out);
void printLine(const std::pair< const int, std::vector< int > >& lineEntry, std::ostream& out);
void printWord(const std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, std::ostream& out);
bool isPositionTaken(const std::pair< const std::string, std::map< int, std::vector< int > > >& entry, int line, int pos);
bool removeLineWord(std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, int line);
void removeLine(std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, int line, bool& lineFound);
void removePosition(std::pair< const int, std::vector< int > >& lineEntry, int column);
void processWordEntry(std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, int column);

void timchishina::doHelp(std::ostream& out)
{
  out << "Commands:\n";
  out << "- create <dict_name> - Сreate a new dictionary with the given <dict_name>.\n";
  out << "- delete <dict_name> - Delete the dictionary with the given <dict_name>.\n";
  out << "- print <dict_name> - Print the contents of the dictionary with the given <name>.\n";
  out << "- add <dict_name> <word> <line> <pos> - Add the <word> to the dictionary with the given <name> to <line> in <pos>.\n";
  out << "- remove <dict_name> <word> - Remove the <word> from the dictionary with the given <dict_name>.\n";
  out << "- addLine <dict_name> - Add a new line at the end of the list in the dictionary with the given <dict_name>.\n";
  out << "- removeLine <dict_name> <line> - Remove the line numbered <line> from the dictionary with the given <dict_name>.\n";
  out << "- removeColumn <dict_name> <column> - Remove the column numbered <column> from the dictionary with the given <dict_name>.\n";
  out << "- find <dict_name> <word> - Display all positions of the <word> in the dictionary with the given <dict_name>.\n";
  out << "- save <dict_name> <path> - Save the dictionary with the given <dict_name> to a file at <path>.\n";
  out << "- load <dict_name> <path> - Create a dictionary with the given <dict_name> from the file at <path>.\n";
  out << "- merge <result> <dict1> <dict2> - Merge dictionaries <dict1> and <dict2> into a new dictionary <result>.\n";
  out << "- intersect <result> <dict1> <dict2> - Intersect dictionaries <dict1> and <dict2> into a new dictionary <result>.\n";
}

void timchishina::doCreate(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
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

void timchishina::doDelete(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  in >> dictName;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  dicts.erase(dict);
  out << "- Dictionary <" << dictName << "> deleted.\n";
}

void printPosition(int position, std::ostream& out)
{
  out << " " << position;
}

void printLine(const std::pair< const int, std::vector< int > >& lineEntry, std::ostream& out)
{
  out << "    Line " << lineEntry.first << ":";
  std::for_each(lineEntry.second.begin(), lineEntry.second.end(), std::bind(printPosition, std::placeholders::_1, std::ref(out)));
  out << "\n";
}

void printWord(const std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, std::ostream& out)
{
  out << "  Word: " << wordEntry.first << "\n";
  std::for_each(wordEntry.second.begin(), wordEntry.second.end(), std::bind(printLine, std::placeholders::_1, std::ref(out)));
}

void timchishina::doPrint(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  in >> dictName;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  out << "- Contents of dictionary <" << dictName << ">:\n";
  std::for_each(dict->second.begin(), dict->second.end(), std::bind(printWord, std::placeholders::_1, std::ref(out)));
}

bool isPositionTaken(const std::pair< const std::string, std::map< int, std::vector< int > > >& entry, int line, int pos)
{
  auto it = entry.second.find(line);
  return (it != entry.second.end() && std::binary_search(it->second.begin(), it->second.end(), pos));
}

void timchishina::doAdd(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "", word = "";
  int line = 0, pos = 0;
  in >> dictName >> word >> line >> pos;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  bool isTaken = std::any_of(dict->second.begin(), dict->second.end(), std::bind(isPositionTaken, std::placeholders::_1, line, pos));
  if (isTaken)
  {
    throw std::logic_error("<POSITION ALREADY TAKEN BY ANOTHER WORD>");
  }
  auto& lineMap = dict->second[word];
  auto& posVector = lineMap[line];
  posVector.insert(std::upper_bound(posVector.begin(), posVector.end(), pos), pos);
  out << "- Added word <" << word << "> at line " << line << ", position " << pos << ".\n";
}

void timchishina::doRemove(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "", word = "";
  in >> dictName >> word;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  auto wordIt = dict->second.find(word);
  if (wordIt == dict->second.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  dict->second.erase(wordIt);
  out << "- Word <" << word << "> removed from dictionary <" << dictName << ">.\n";
}

void timchishina::doAddLine(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  in >> dictName;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::vector<int> lineNumbers;
  for (const auto& wordEntry : dict->second)
  {
    for (const auto& lineEntry : wordEntry.second)
    {
      lineNumbers.push_back(lineEntry.first);
    }
  }
  int newLine = 0;
  if (lineNumbers.empty())
  {
    newLine = 1;
  }
  else
  {
    newLine = *std::max_element(lineNumbers.begin(), lineNumbers.end()) + 1;
  }
  out << "- Added new line " << newLine << " to dictionary <" << dictName << ">.\n";
}

bool removeLineWord(std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, int line)
{
  auto& lineMap = wordEntry.second;
  auto lineIt = lineMap.find(line);
  if (lineIt != lineMap.end())
  {
    lineMap.erase(lineIt);
    return true;
  }
  return false;
}

void removeLine(std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, int line, bool& lineFound)
{
  if (removeLineWord(wordEntry, line))
  {
    lineFound = true;
  }
}

void timchishina::doRemoveLine(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  int line = 0;
  in >> dictName >> line;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  auto& wordMap = dict->second;
  bool lineFound = false;
  std::for_each(wordMap.begin(), wordMap.end(), std::bind(removeLine, std::placeholders::_1, line, std::ref(lineFound)));
  if (!lineFound)
  {
    throw std::logic_error("<LINE NOT FOUND>");
  }
  auto it = wordMap.begin();
  while (it != wordMap.end())
  {
    if (it->second.empty())
    {
      it = wordMap.erase(it); 
    }
    else
    {
      ++it;
    }
  }
  out << "- Removed line " << line << " from dictionary <" << dictName << ">.\n";
}

void removePosition(std::pair< const int, std::vector< int > >& lineEntry, int column)
{
  std::vector< int >& positions = lineEntry.second;
  positions.erase(std::remove(positions.begin(), positions.end(), column), positions.end());
}

void processWordEntry(std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, int column)
{
  std::for_each(wordEntry.second.begin(), wordEntry.second.end(), std::bind(removePosition, std::placeholders::_1, column));
  auto it = wordEntry.second.begin();
  while (it != wordEntry.second.end())
  {
    if (it->second.empty())
    {
      it = wordEntry.second.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void timchishina::doRemoveColumn(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName = "";
  int column = 0;
  in >> dictName >> column;
  auto dict = dicts.find(dictName);
  if (dict == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::for_each(dict->second.begin(), dict->second.end(), std::bind(processWordEntry, std::placeholders::_1, column));
  auto& wordMap = dict->second;
  auto it = wordMap.begin();
  while (it != wordMap.end())
  {
    if (it->second.empty())
    {
      it = wordMap.erase(it);
    }
    else
    {
      ++it;
    }
  }
  out << "Column " << column << " removed from dictionary <" << dictName << ">\n";
}

