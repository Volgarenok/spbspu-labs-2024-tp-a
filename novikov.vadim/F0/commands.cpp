#include "commands.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iterator>
#include "word.hpp"

void novikov::insert(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;
  storage.at(dictionary)[key].insert(value);
}

void novikov::open(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string file;

  in >> dictionary >> file;

  std::ifstream fin(file);

  if (!fin.is_open())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary new_dictionary;
  Word temp;

  while (fin >> temp)
  {
    new_dictionary[temp.value.first].insert(temp.value.second);
  }

  storage[dictionary] = std::move(new_dictionary);
}

void novikov::print(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  in >> dictionary;

  auto res = storage.at(dictionary);

  for (const auto& i : res)
  {
    for (const auto& j : i.second)
    {
      out << Word{ { i.first, j } } << "\n";
    }
  }
}
