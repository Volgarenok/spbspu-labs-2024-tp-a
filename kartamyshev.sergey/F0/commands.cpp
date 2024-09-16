#include "commands.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

void kartamyshev::help(std::ostream& out)
{
  out << "List of commands\n";
  out << " - create <name> - create new dictioanry\n";
  out << " - fill_in <file.txt> <name> - fill dictionary from file\n";
  out << " - list_information <name> - display dictionary information\n";
  out << " - search <word> <name> - search word in dictionary\n";
  out << " - delete_dictionary <name> - delete dictionary\n";
  out << " - merge <name 1> <name 2> - enter the data of the second dictionary into the first\n";
  out << " - get_merge <name 1> <name 2> <name 3> - merge two dictionaries into an existing third one\n";
  out << " - list_popular <name> <count> - display the number of popular words\n";
  out << " - get_intersection <name 1> <name 2> <name 3> - create a third dictionary and enter the data of the first and second into it\n";
  out << " - list_rare <name> <count> -  display the number of rare words\n";
  out << " - clear <name> - clear dictionary\n";
  out << " - list_range_words <name> <count> <count> - display the range words\n";
}


void kartamyshev::create(DictionarySet& set, std::istream& in)
{
  std::string name;
  in >> name;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }
  if (set.count(name) > 0)
  {
    throw std::logic_error("<DICTIOARY EXISTS>");
  }
  set[name];
}
