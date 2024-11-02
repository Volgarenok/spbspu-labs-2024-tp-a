#include "commands.hpp"

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
