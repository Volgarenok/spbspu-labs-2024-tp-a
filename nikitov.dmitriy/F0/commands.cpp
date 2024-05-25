#include "commands.hpp"

void nikitov::printCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;

  if (dictName != "all")
  {
    auto value = dictOfDicts.find(dictName);
    if (value != dictOfDicts.cend())
    {
      value->second.printDictionary(output);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  else
  {
    for (auto i = dictOfDicts.begin(); i != dictOfDicts.end(); ++i)
    {
      i->second.printDictionary(output);
    }
  }
}