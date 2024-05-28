#include "CLA.hpp"
#include <fstream>

void baranov::printHelp(std::ostream & out)
{
  out << "1. New dictionary creating:\n";
  out << "   create <dict_name>\n";
  out << "   create <dict_name> <in_file>\n\n";
  out << "2. Cleaning the dictionary:\n";
  out << "   clear <dict_name>\n\n";
  out << "3. Deleting a dictionary:\n";
  out << "   delete <dict_name>\n\n";
  out << "4. Adding to the dictionary:\n";
  out << "   addwords <dict_name> <in_file>\n\n";
  out << "5. Printing the frequency of the word:\n";
  out << "   printcount <word> <dict_name>\n";
  out << "   printcount <word>\n\n";
  out << "6. Printing the dictionary in alphabetical order:\n";
  out << "   printdict <dict_name>\n\n";
  out << "7. Printing a dictionary in order of decreasing word frequency\n";
  out << "   printtop <dict_name> <count>\n";
  out << "   printtop <dict_name>\n\n";
  out << "8. Combining dictionaries:\n";
  out << "   join <first_dict_name> <second_dict_name> <out_dict_name>\n\n";
  out << "9. Dictionary intersection:\n";
  out << "   intersect <first_dict_name> <second_dict_name> <out_dict_name>\n\n";
  out << "10.Saving a dictionary to a file:\n";
  out << "   save <dict_name> <out_file>\n";
}

void baranov::readDict(std::map< std::string, dict_t > & dicts, const char * argv[])
{
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    throw std::logic_error("Invalid file name\n");
  }
  std::string dictName;
  file >> dictName;
  std::string word;
  size_t count;
  dict_t temp;
  while (file >> word >> count)
  {
    temp[word] = count;
  }
  if (file.fail())
  {
    throw std::logic_error("Cannot read dictionary\n");
  }
  dicts[dictName] = temp;
}

