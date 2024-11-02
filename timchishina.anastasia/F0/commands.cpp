#include "commands.hpp"
#include <algorithm>
#include <functional>

void printPosition(int position, std::ostream& out);
void printLine(const std::pair< const int, std::vector< int > >& lineEntry, std::ostream& out);
void printWord(const std::pair< const std::string, std::map< int, std::vector< int > > >& wordEntry, std::ostream& out);
bool isPositionTaken(const std::pair< const std::string, std::map< int, std::vector< int > > >& entry, int line, int pos);

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

