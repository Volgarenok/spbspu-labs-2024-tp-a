#include "cmd.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iterator>

void ishmuratov::create_dict(dict_t & dictionaries, std::istream & input)
{
  unit_t content;
  std::string name;
  input >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    dictionaries.insert(std::make_pair(name, content));
  }
  else
  {
    throw std::out_of_range("Dictionary already exists!");
  }
}

void ishmuratov::delete_dict(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  input >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  dictionaries.erase(name);
}

void ishmuratov::add_key(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string key;
  std::string value;
  value_t values;

  input >> name >> key >> value;
  values.push_back(value);

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  if (dictionaries.at(name).find(key) != dictionaries.at(name).end())
  {
    throw std::invalid_argument("Key already exists!");
  }
  else
  {
    dictionaries.at(name).insert(std::make_pair(key, values));
  }
}

void ishmuratov::add_value(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string key;
  std::string value;

  input >> name >> key >> value;

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  if (dictionaries.at(name).find(key) == dictionaries.at(name).end())
  {
    throw std::invalid_argument("Key wasn't found!");
  }
  dictionaries.at(name).at(key).push_back(value);
}

void ishmuratov::remove_key(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string key;

  input >> name >> key;

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  if (dictionaries.at(name).find(key) == dictionaries.at(name).end())
  {
    throw std::invalid_argument("Key wasn't found!");
  }
  else
  {
    dictionaries.at(name).erase(key);
  }
}

void ishmuratov::print_dict(const dict_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string name;
  input >> name;

  if (dictionaries.find(name) == dictionaries.cend())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  if (dictionaries.at(name).empty())
  {
    throw std::underflow_error("This dictionary is empty!");
  }

  unit_t to_print = dictionaries.at(name);

  for (auto pair = to_print.cbegin(); pair != to_print.cend(); ++pair)
  {
    output << pair->first << "\n";
    size_t count = 1;
    for (auto value = pair->second.cbegin(); value != pair->second.cend(); ++value)
    {
      output << count << ". " << *value << "\n";
      ++count;
    }
    auto check = pair;
    if (++check != dictionaries.at(name).cend())
    {
      output << "\n";
    }
  }
  std::cout << to_str(*to_print.begin());
}

void ishmuratov::get_value(const dict_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string name;
  std::string key;
  input >> name >> key;
  if (dictionaries.find(name) == dictionaries.cend())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  if (dictionaries.at(name).find(key) == dictionaries.at(name).cend())
  {
    throw std::out_of_range("Key wasn't found!");
  }

  auto found_key = dictionaries.at(name).at(key);
  std::copy(found_key.cbegin(), found_key.cend(), std::ostream_iterator<std::string>(output, " "));
}

void ishmuratov::save(const dict_t & dictionaries, std::istream &input)
{
  std::string file_name;
  input >> file_name;
  std::ofstream out_file(file_name);
  if (!out_file.is_open())
  {
    throw std::runtime_error("Error occurred while opening file!");
  }

  for (auto dict = dictionaries.cbegin(); dict != dictionaries.cend(); ++dict)
  {
    out_file << dict->first << "\n";
    for (auto pair = dict->second.cbegin(); pair != dict->second.cend(); ++pair)
    {
      out_file << pair->first;
      for (auto value = pair->second.cbegin(); value != pair->second.cend(); ++value)
      {
        out_file << " " << *value;
      }
      out_file << "\n";
    }
    out_file << "\n";
  }
}

void ishmuratov::read(dict_t & dictionaries, std::istream & input)
{
  std::ifstream in_file;
  std::string file_name;
  input >> file_name;
  in_file.open(file_name);
  if (!in_file.is_open())
  {
    throw std::runtime_error("Error occurred while opening file!");
  }
  try
  {
    input_dictionary(dictionaries, in_file);
  }
  catch (...)
  {
    throw std::invalid_argument("Invalid file content!");
  }
}

void ishmuratov::renamedict(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string new_name;
  input >> name >> new_name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }
  if (dictionaries.find(new_name) != dictionaries.end())
  {
    throw std::out_of_range("Dictionary with this name already exists!");
  }

  dictionaries.insert(std::make_pair(new_name, dictionaries.at(name)));
  dictionaries.erase(name);
}

void ishmuratov::intersect(dict_t & dictionaries, std::istream & input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  input >> new_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }

  unit_t temp = intersect_impl(dictionaries.at(first_name), dictionaries.at(second_name));
  while (input.get() != '\n' && input >> second_name)
  {
    temp = intersect_impl(temp, dictionaries.at(second_name));
  }
  dictionaries.insert(std::make_pair(new_name, temp));
}

ishmuratov::unit_t ishmuratov::intersect_impl(const unit_t & first, const unit_t & second)
{
  unit_t inter_dict;
  auto pred = std::bind(is_inside, std::placeholders::_1, std::cref(second));
  std::copy_if(first.cbegin(), first.cend(), std::inserter(inter_dict, inter_dict.end()), pred);
  return inter_dict;
}

bool ishmuratov::is_inside(const std::pair< std::string, std::list< std::string > > & pair, const unit_t & second)
{
  return second.find(pair.first) != second.cend();
}

void ishmuratov::uniond(dict_t & dictionaries, std::istream & input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  input >> new_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exist!");
  }

  unit_t temp = union_impl(dictionaries.at(first_name), dictionaries.at(second_name));
  while (input.get() != '\n' && input >> second_name)
  {
    temp = union_impl(temp, dictionaries.at(second_name));
  }
  dictionaries.insert(std::make_pair(new_name, temp));
}

ishmuratov::unit_t ishmuratov::union_impl(const unit_t & first, const unit_t & second)
{
  unit_t union_dict;
  std::copy(first.cbegin(), first.cend(), std::inserter(union_dict, union_dict.end()));
  auto pred = std::not_fn(std::bind(is_inside, std::placeholders::_1, std::cref(first)));
  std::copy_if(second.cbegin(), second.cend(), std::inserter(union_dict, union_dict.end()), pred);
  return union_dict;
}
