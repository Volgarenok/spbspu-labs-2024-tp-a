#include "input.hpp"

void ishmuratov::input_dictionary(dict_t & dictionaries, std::istream &input)
{
  std::string name;
  while (std::getline(input, name))
  {
    unit_t unit;
    std::string key;
    while (input >> key)
    {
      value_t values;
      std::string value;
      while (input >> value)
      {
        values.push_back(value);
        if (input.get() == '\n')
        {
          break;
        }
      }
      unit.insert(std::make_pair(key, values));
      if (input.get() == '\n')
      {
        break;
      }
      else
      {
        input.unget();
      }
    }
    dictionaries.insert(std::make_pair(name, unit));
  }
}

void ishmuratov::print_help(std::ostream &output)
{
  output << "Commands:\n";
  output << "1. createdict <dictionary name> - create empty dictionary\n";
  output << "2. deletedict <dictionary name> - delete dictionary\n";
  output << "3. addkey <dictionary name> <key> <value> - add key and value to dictionary\n";
  output << "4. addvalue <dictionary name> <key> <value> - add value to an existent key of dictionary\n";
  output << "5. removekey <dictionary name> <key> - remove key from a dictionary\n";
  output << "6. printdict <dictionary name> - print a whole dictionary\n";
  output << "7. getvalue <dictionary name> <key> - print all values of key in dictionary\n";
  output << "8. save <file name> - save all current dictionaries to a file\n";
  output << "9. read <file name> <dictionary name> - read dictionary from a file ";
  output << "(if dictionary name is not specified, read all dictionaries)\n";
  output << "10. rename <dictionary name> - rename a dictionary\n";
  output << "11. intersect <new dictionary> <first dictionary > ... - write intersection of multiple dictionaries ";
  output << "to a new dictionary\n";
  output << "12. union <new dictionary> <first dictionary > ... - write union of multiple dictionaries ";
  output << "to a new dictionary\n";
}
