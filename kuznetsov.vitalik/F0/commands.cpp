#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <memory>


void kuznetsov::command_create_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::string dictionare_name;
  in >> dictionare_name;

  if (data.find(dictionare_name) != data.end())
  {
    out << "A dictionary with this name has already been created\n";
  }
  else
  {
    data[dictionare_name] = {};
  }
}
void kuznetsov::command_add_word(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{

}

