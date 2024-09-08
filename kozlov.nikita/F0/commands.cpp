#include "commands.hpp"

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
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }
  dicts[dictName] = {};
  out << "Dictionary " << dictName << " created.\n";
}
