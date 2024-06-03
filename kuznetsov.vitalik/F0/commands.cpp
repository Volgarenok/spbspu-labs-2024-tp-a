#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <vector>
#include "additionalcommands.hpp"

void kuznetsov::command_add_word(std::map< std::string, frequency_dictionary >& data, std::istream& in)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name = "";
  std::string word = "";
  in >> dictionary_name;
  in >> word;
  if (!check_word(word))
  {
    throw std::invalid_argument("The word was set incorrectly");
  }
  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary& data_word = data[dictionary_name];
    if (data_word.find(word) == data_word.end())
    {
      data_word[word] = 1;
    }
    else
    {
      size_t& volume = data[dictionary_name].at(word);
      ++volume;
    }
  }
  else
  {
    throw std::logic_error("A dictionary with the same name was not found");
  }
}

void kuznetsov::command_delete_word(std::map< std::string, frequency_dictionary >& data, std::istream& in)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name = "";
  std::string word = "";
  in >> dictionary_name;
  in >> word;
  if (!check_word(word))
  {
    throw std::invalid_argument("The word was set incorrectly");
  }
  if (data[dictionary_name].empty())
  {
    throw std::logic_error("Dictionary empty");
  }
  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary& data_word = data[dictionary_name];
    auto it = data_word.find(word);
    if (it != data_word.end())
    {
      data_word.erase(it);
    }
    else
    {
      throw std::logic_error("Word in this dictionary not found");
    }
  }
  else
  {
    throw std::logic_error("A dictionary with the same name was not found");
  }
}

void kuznetsov::command_output(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::string dictionary_name = "";
  in >> dictionary_name;

  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary data_word = data[dictionary_name];
    if (data_word.empty())
    {
      throw std::logic_error("Dictioanry empty");
    }
    else
    {
      frequency_dictionary::iterator it;
      for (it = data_word.begin(); it != data_word.end(); ++it)
      {
        std::pair< std::string, size_t > word = *it;
        out << word.first << "-" << word.second << '\n';
      }
    }
  }
  else
  {
    throw std::logic_error("A dictionary with the same name was not found");
  }
}

void kuznetsov::command_create_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::string dictionary_name = "";
  in >> dictionary_name;

  if (data.find(dictionary_name) == data.end())
  {
    data[dictionary_name] = {};
  }
  else
  {
    throw std::logic_error("A dictionary with this name has already been created");
  }
}

void kuznetsov::command_delete_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name = "";
  in >> dictionary_name;
  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary& data_word = data[dictionary_name];
    data_word.clear();
    data.erase(dictionary_name);
  }
  else
  {
    throw std::logic_error("A dictionary with the same name was not found");
  }
}

void kuznetsov::command_search_in_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name = "";
  in >> dictionary_name;
  std::string word = "";
  in >> word;
  if (!check_word(word))
  {
    throw std::invalid_argument("The word was set incorrectly");
  }
  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary& data_word = data[dictionary_name];
    if (data_word.find(word) != data_word.cend())
    {
      out << "The word is present in this dictionary\n";
    }
    else
    {
      out << "The word isn't present in this dictionary\n";
    }
  }
  else
  {
    throw std::logic_error("A dictionary with the same name was not found");
  }
}

void kuznetsov::command_search_in_all_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string word = "";
  in >> word;
  if (data.empty())
  {
    throw std::logic_error("Not a single dictionary has been created");
  }
  if (!check_word(word))
  {
    throw std::invalid_argument("The word was set incorrectly");
  }
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    for (auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
    {
      if ((*it2).first == word)
      {
        out << (*it).first << " ";
      }
    }
  }
  out << '\n';
}

void kuznetsov::command_show_dictionary(std::map< std::string, frequency_dictionary >& data, std::ostream& out)
{
  if (data.empty())
  {
    throw std::logic_error("Not a single dictionary has been created");
  }
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    out << (*it).first << " ";
  }
  out << '\n';
}

void kuznetsov::command_add_words_from_file(std::map< std::string, frequency_dictionary >& data, std::istream& in)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::string dictionary_name = "";
  in >> dictionary_name;
  std::string name_file = "";
  in >> name_file;

  if (data.find(dictionary_name) == data.end())
  {
    throw std::logic_error("A dictionary with the same name was not found");
  }

  frequency_dictionary& data_word = data[dictionary_name];
  std::ifstream file(name_file);

  if (!file.is_open())
  {
    throw std::runtime_error("File not open");
  }
  if (file.eof())
  {
    throw std::runtime_error("File empty");
  }
  std::string word = "";
  while (!file.eof())
  {
    file >> word;
    if (data_word.find(word) == data_word.end())
    {
      data_word[word] = 1;
    }
    else
    {
      size_t& volume = data[dictionary_name].at(word);
      ++volume;
    }
  }
}

void kuznetsov::command_merge(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string new_dictionary_name ="";
  in >> new_dictionary_name;
  std::string dictionary_name1 = "";
  in >> dictionary_name1;
  std::string dictionary_name2 = "";
  in >> dictionary_name2;

  if (data.find(new_dictionary_name) != data.end())
  {
    throw std::logic_error("A dictionary with this name has already been created");
  }

  if (!(data.find(dictionary_name1) != data.end()))
  {
    out << "Dictionary \"" << dictionary_name1 << "\" not found\n";
    return;
  }

  if (!(data.find(dictionary_name2) != data.end()))
  {
    out << "Dictionary \"" << dictionary_name2 << "\" not found\n";
    return;
  }

  if (data[dictionary_name1].empty() && data[dictionary_name2].empty())
  {
    throw std::logic_error("Dictionaries are empty");
  }

  frequency_dictionary& dict = data[new_dictionary_name];

  frequency_dictionary& dict1 = data[dictionary_name1];
  auto it = dict1.begin();
  while (it != dict1.end())
  {
    dict[(*it).first] = (*it).second;
    ++it;
  }

  frequency_dictionary& dict2 = data[dictionary_name2];
  it = dict2.begin();
  while (it != dict2.end())
  {
    if (dict.find((*it).first) != dict.end())
    {
      dict[(*it).first] += (*it).second;
      ++it;
    }
    else
    {
      dict[(*it).first] = (*it).second;
      ++it;
    }
  }
}

void kuznetsov::command_intersection(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string new_dictionary_name = "";
  in >> new_dictionary_name;
  std::string dictionary_name1 = "";
  in >> dictionary_name1;
  std::string dictionary_name2 = "";
  in >> dictionary_name2;

  if (data.find(new_dictionary_name) != data.end())
  {
    throw std::logic_error("A dictionary with this name has already been created");
  }

  if (!(data.find(dictionary_name1) != data.end()))
  {
    out << "Dictionary \"" << dictionary_name1 << "\" not found\n";
    return;
  }

  if (!(data.find(dictionary_name2) != data.end()))
  {
    out << "Dictionary \"" << dictionary_name2 << "\" not found\n";
    return;
  }

  if (data[dictionary_name1].empty() || data[dictionary_name2].empty())
  {
    throw std::logic_error("No intersections because one of dictionaries is empty");
  }

  frequency_dictionary& dict = data[new_dictionary_name];
  frequency_dictionary& dict1 = data[dictionary_name1];
  frequency_dictionary& dict2 = data[dictionary_name2];

  auto it1 = dict1.begin();
  auto it2 = dict2.begin();

  while (it1 != dict1.end() && it2 != dict2.end())
  {
    if ((*it1).first == (*it2).first)
    {
      dict[(*it1).first] = std::min((*it1).second, (*it2).second);
      ++it1;
      ++it2;
    }
    else if ((*it1).first < (*it2).first)
    {
      ++it1;
    }
    else
    {
      ++it2;
    }
  }
}

void kuznetsov::command_top_popular_words(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  size_t count = 0;
  in >> count;
  if (!in)
  {
    throw std::invalid_argument("Argument error");
  }
  std::vector< frequency_dictionary > dict = {};
  std::string dictionary_name = "";
  while (in.peek() != '\n')
  {
    in >> dictionary_name;
    if (data.find(dictionary_name) != data.end())
    {
      if (data[dictionary_name].empty())
      {
        out << "Dictionary \"" << dictionary_name << "\" empty\n";
        return;
      }
      dict.push_back(data[dictionary_name]);
    }
    else
    {
      out << "Dictionary \"" << dictionary_name << "\" not found\n";
      return;
    }
  }
  std::vector< std::pair< std::string, size_t > > arr = return_top_words(dict);
  int place = 1;
  auto it = arr.begin();
  while (count != 0)
  {
    out << place << " | " << (*it).first << " " << (*it).second << '\n';
    --count;
    ++it;
    ++place;
  }
}

void kuznetsov::command_create_dictionary_popular_words(std::map< std::string, frequency_dictionary >& data,
 std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  size_t count = 0;
  in >> count;
  if (!in)
  {
    throw std::invalid_argument("Argument error");
  }
  std::vector< frequency_dictionary > dict = {};
  std::string dictionary_name = "";
  std::string new_dictionary_name = "";
  in >> new_dictionary_name;
  if (data.find(new_dictionary_name) != data.end())
  {
    throw std::logic_error("A dictionary with this name has already been created");
  }
  while (in.peek() != '\n')
  {
    in >> dictionary_name;
    if (data.find(dictionary_name) != data.end())
    {
      dict.push_back(data[dictionary_name]);
    }
    else
    {
      out << "Dictionary \"" << dictionary_name << "\" not found\n";
      return;
    }
  }
  std::vector< std::pair< std::string, size_t > > arr = return_top_words(dict);
  auto it = arr.begin();
  while (count != 0)
  {
    data[new_dictionary_name][(*it).first] = (*it).second;
    ++it;
    --count;
  }
}

void kuznetsov::command_help(std::ostream& out)
{
  out << "COMMANDS:\n\n";
  out << "create_dictionary < dictionary_name > - create new dictionary.\n\n";
  out << "delete_dictionary < dictionary name > - delete dictionty.\n\n";
  out << "add_word < dictionary name > < word > - add word to dictionary.\n\n";
  out << "delete_word < dictionary name > < word > - delete word from dictionary.\n\n";
  out << "add_words_from_file < dictionary name > - add words from file in dictionary\n\n";
  out << "output < dictionary name > - output words from dictionary\n\n";
  out << "show_dictionary - output list of dictionary.\n\n";
  out << "search_in_dictionary < dictionary name > < word > - serch word in dictionary.\n\n";
  out << "search_in_all_dictionary < word > - output a list of dictionaries with the given word.\n\n";
  out << "merge < new dictionary name > < dictionary name 1 > < dictionary name 2 > - ";
  out << "combines two dictionaries into one\n\n";
  out << "intersection < new dictionary name > < dictionary name 1 > < dictionary name 2 > - n";
  out << "creates a dictionary from intersections\n\n";
  out << "top_popular_words < quantity word > < dictionary name 1 > ... < dictionary name n > - ";
  out << "displays a list of words that are most common(from all dictionaries)\n\n";
  out << "create_dictionary_from_top_popular_words < quantity word > < new dictionary name > ";
  out << "< dictionary name 1 > ... < dictionary name n > - create a dictionary from the words ";
  out << "that are most common(from all dictionaries)\n\n";
  out << "save_data - save data\n";
  out << "load_data - load data\n";
}

void kuznetsov::command_save(std::map< std::string, frequency_dictionary >& data)
{
  std::ofstream file("save.txt");
  if (!file.is_open())
  {
    throw std::runtime_error("File not open");
  }
  file.clear();
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    file << (*it).first << " " << (*it).second.size() << " ";
    for (auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
    {
      file << (*it2).first << " " << (*it2).second << " ";
    }
    file << '\n';
  }
}

void kuznetsov::command_load(std::map< std::string, frequency_dictionary >& data)
{
  std::ifstream file("save.txt");
  if (!file.is_open())
  {
    throw std::runtime_error("File not open");
  }
  std::string dictionary_name = "";
  size_t size = 0;
  size_t volume = 0;
  std::string word = "";
  while (!file.eof())
  {
    file >> dictionary_name >> size;
    frequency_dictionary data_word;
    for (size_t i = 0; i < size; ++i)
    {
      file >> word >> volume;
      if (!check_word(word))
      {
        data[dictionary_name].clear();
        throw std::invalid_argument("The word was set incorrectly");
      }
      data[dictionary_name][word] = volume;
    }
  }
}

void kuznetsov::command_check(std::ostream& out)
{
  std::ifstream file("save.txt");
  if (!file.is_open())
  {
    throw std::runtime_error("File not open");
  }
  std::string dictionary_name = "";
  size_t size = 0;
  size_t volume = 0;
  std::string word = "";
  while (!file.eof())
  {
    file >> dictionary_name >> size;
    while (size)
    {
      file >> word >> volume;
      if (!check_word(word))
      {
        throw std::runtime_error("File not correct");
      }
      --size;
    }
  }
  out << "File correct\n";
}
