#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include "additionalcommands.hpp"

void kuznetsov::command_add_word(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name;
  std::string word;
  in >> dictionary_name;
  in >> word;
  if (data.find(dictionary_name) != data.end())
  {

    frequency_dictionary data_word = data[dictionary_name];
    if (data_word.find(word) == data_word.end())
    {
      data_word[word] = 1;
      data[dictionary_name] = data_word;
    }
    else
    {
      size_t& volume = data[dictionary_name].at(word);
      ++volume;
    }
  }
  else
  {
    out << "A dictionary with the same name was not found\n";
  }
}

void kuznetsov::command_delete_word(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name;
  std::string word;
  in >> dictionary_name;
  in >> word;
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
      out << "Word in this dictionary not found\n";
    }
  }
  else
  {
    out << "A dictionary with the same name was not found\n";
  }
}

void kuznetsov::command_output(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::string dictionary_name;
  in >> dictionary_name;

  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary data_word = data[dictionary_name];
    if (data_word.empty())
    {
      out << "Dictioanry empty\n";
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
    out << "A dictionary with the same name was not found\n";
  }
}

void kuznetsov::command_create_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::string dictionary_name;
  in >> dictionary_name;

  if (data.find(dictionary_name) == data.end())
  {
    data[dictionary_name] = {};
  }
  else
  {
    out << "A dictionary with this name has already been created\n";
  }
}

void kuznetsov::command_delete_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name;
  in >> dictionary_name;
  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary& data_word = data[dictionary_name];
    data_word.clear();
    data.erase(dictionary_name);
  }
  else
  {
    out << "A dictionary with the same name was not found\n";
  }
}

void kuznetsov::command_search_in_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name;
  in >> dictionary_name;
  std::string word;
  in >> word;
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
    out << "A dictionary with the same name was not found\n";
  }
}

void kuznetsov::command_search_in_all_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string word;
  in >> word;
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    for (auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
    {
      if ((*it2).first == word)
      {
        out << (*it).first << " ";
        continue;
      }
    }
  }
  out << '\n';
}

void kuznetsov::command_show_dictionary(std::map< std::string, frequency_dictionary >& data, std::ostream& out)
{
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    out << (*it).first << " ";
  }
  out << '\n';
}

void kuznetsov::command_add_words_from_file(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string dictionary_name;
  in >> dictionary_name;
  std::string name_file;
  in >> name_file;
  if (data.find(dictionary_name) != data.end())
  {
    frequency_dictionary& data_word = data[dictionary_name];
    std::ifstream file(name_file);
    if (!file.is_open())
    {
      out << "File not open\n";
    }
    else
    {
      std::string word;
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
  }
  else
  {
    out << "A dictionary with the same name was not found\n";
    return;
  }
}


void kuznetsov::command_merge(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string new_dictionary_name;
  in >> new_dictionary_name;
  std::string dictionary_name1;
  in >> dictionary_name1;
  std::string dictionary_name2;
  in >> dictionary_name2;

  if (data.find(new_dictionary_name) != data.end())
  {
    out << "Dictionary with this name already create\n";
    return;
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
    out << "Dictionaries are empty\n";
    return;
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
