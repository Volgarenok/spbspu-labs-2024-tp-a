#include "commands.hpp"
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <numeric>

using mapDict = std::map< std::string, kornienko::Dictionary >;
void kornienko::createDictionary(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string newName;
  in >> newName;
  for (auto element : dictionaries)
  {
    if (element.first == newName)
    {
      throw std::logic_error("ALREADY EXIST\n");
    }
  }
  dictionaries[newName];
}

void kornienko::deleteDictionary(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string name;
  in >> name;
  auto iter = dictionaries.find(name);
  if (iter != dictionaries.end())
  {
      dictionaries.erase(name);
  }
  else
  {
      throw std::logic_error("DICTIONARY DOESN’T EXIST\n");
  }
}
