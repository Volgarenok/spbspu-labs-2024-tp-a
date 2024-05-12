#include "commands.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>
#include "predicates.hpp"
#include "word.hpp"

void novikov::insert(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;

  if (storage.at(dictionary)[key].find(value) != storage.at(dictionary)[key].end())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  storage.at(dictionary)[key].insert(value);
}

void novikov::search(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;

  auto dict = storage.at(dictionary);

  for (const auto& i : dict)
  {
    if (contains(i.first, key))
    {
      for (const auto& j : i.second)
      {
        if (contains(j, value))
        {
          out << Word{ { i.first, j } } << "\n";
        }
      }
    }
  }
}

void novikov::searchKeys(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string key;

  in >> dictionary >> key;

  auto dict = storage.at(dictionary);

  for (const auto& i : dict)
  {
    if (contains(i.first, key))
    {
      for (const auto& j : i.second)
      {
          out << Word{ { i.first, j } } << "\n";
      }
    }
  }
}

void novikov::searchValues(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string value;

  in >> dictionary >> value;

  auto dict = storage.at(dictionary);

  for (const auto& i : dict)
  {
    for (const auto& j : i.second)
    {
      if (contains(j, value))
      {
        out << Word{ { i.first, j } } << "\n";
      }
    }
  }
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

  fin.close();

  storage[dictionary] = std::move(new_dictionary);
}

void novikov::close(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  in >> dictionary;

  if (storage.find(dictionary) == storage.end())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  storage.erase(dictionary);
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
