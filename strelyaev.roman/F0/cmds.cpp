#include "cmds.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>

void strelyaev::addDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string >{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }
  std::map< std::string, std::vector< std::string > > new_dict;
  dictionaries[name] = new_dict;
}

void strelyaev::deleteDictionary(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
   throw std::logic_error("<BOOK NOT FOUND>");
  }
  dictionaries.erase(name);
}

void strelyaev::addWord(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
   throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& needed_dict = dictionaries[name];
  std::string word = "";
  std::string translation = "";
  in >> word >> translation;
  needed_dict[word].push_back(translation);
}

void strelyaev::removeWord(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
   throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& needed_dict = dictionaries[name];
  std::string word = "";
  in >> word;
  try
  {
    needed_dict.at(word);
  }
  catch (...)
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  needed_dict.erase(word);
}

void strelyaev::translate(std::ostream& out,
    std::istream& in,
    const std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  std::string eng_word = "";
  in >> name >> eng_word;
  if (dictionaries.find(name) == dictionaries.end())
  {
   throw std::logic_error("<BOOK NOT FOUND>");
  }
  const std::map< std::string, std::vector< std::string > >& needed_dict = dictionaries.at(name);

  if (needed_dict.find(eng_word) == needed_dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  const std::vector< std::string > translations = needed_dict.at(eng_word);
  out << eng_word << " ";
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator< std::string >(out, " "));
  out << "\n";
  return;
}

void strelyaev::mergeDictionaries(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string first_name = "";
  std::string second_name = "";
  std::map< std::string, std::vector< std::string > > result;
  in >> first_name >> second_name;
  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& first = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second = dictionaries[second_name];
  for (auto it = second.cbegin(); it != second.cend(); it++)
  {
    const std::string& key = it->first;
    const std::vector< std::string >& values = it->second;
    if (first.find(key) != first.end())
    {
      first[key].insert(first[key].end(), values.begin(), values.end());
    }
    else
    {
      first[key] = values;
    }
  }
}

void strelyaev::getIntersection(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string new_dict_name, first_name, second_name;
  in >> new_dict_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  const std::map< std::string, std::vector<std::string > >& first_dict = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second_dict = dictionaries[second_name];
  std::map<std::string, std::vector<std::string>> result_dict;

  for (auto it1 = first_dict.begin(); it1 != first_dict.end(); ++it1)
  {
    const std::string& word = it1->first;
    const std::vector< std::string >& first_translations = it1->second;

    auto it2 = second_dict.find(word);
    if (it2 != second_dict.end())
    {
      const std::vector< std::string >& second_translations = it2->second;
      std::vector< std::string > common_translations;
      for (auto trans_it = first_translations.begin(); trans_it != first_translations.end(); ++trans_it)
      {
        if (std::find(second_translations.begin(), second_translations.end(), *trans_it) != second_translations.end())
        {
          common_translations.push_back(*trans_it);
        }
      }
      if (!common_translations.empty())
      {
        result_dict[word] = common_translations;
      }
    }
  }
  dictionaries[new_dict_name] = result_dict;
}

void strelyaev::getCombining(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string new_dict_name, first_name, second_name;
  in >> new_dict_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& first_dict = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second_dict = dictionaries[second_name];
  std::map< std::string, std::vector< std::string > > result_dict = {};

  for (auto it = first_dict.begin(); it != first_dict.end(); ++it)
  {
    result_dict.insert(*it);
  }

  for (auto it = second_dict.begin(); it != second_dict.end(); ++it)
  {
    const std::string& word = it->first;
    const std::vector< std::string >& translations = it->second;
    auto result_it = result_dict.find(word);
    if (result_it != result_dict.end())
    {
      std::vector< std::string >& result_translations = result_it->second;
      for (auto trans_it = translations.begin(); trans_it != translations.end(); ++trans_it)
      {
        if (std::find(result_translations.begin(), result_translations.end(), *trans_it) == result_translations.end())
        {
          result_translations.push_back(*trans_it);
        }
      }
    }
    else
    {
      result_dict.insert(*it);
    }
  }
  dictionaries[new_dict_name] = result_dict;
}


void strelyaev::getDifference(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string new_dict_name = "";
  std::string first_name = "";
  std::string second_name = "";
  std::string comparison_type = "";
  in >> new_dict_name >> first_name >> second_name >> comparison_type;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end()) {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& first_dict = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second_dict = dictionaries[second_name];
  std::map< std::string, std::vector< std::string > > result_dict;

  if (comparison_type == "translation")
  {
    for (auto it = first_dict.begin(); it != first_dict.end(); ++it)
    {
      const std::string& word = it->first;
      const std::vector< std::string >& first_translations = it->second;
      auto second_it = second_dict.find(word);
      if (second_it != second_dict.end()) {
        const std::vector< std::string >& second_translations = second_it->second;
        std::vector< std::string > difference_translations;
        std::set_difference(first_translations.begin(),
            first_translations.end(),
            second_translations.begin(),
            second_translations.end(),
            std::back_inserter(difference_translations));
        if (!difference_translations.empty())
        {
          result_dict[word] = difference_translations;
        }
      }
      else
      {
        result_dict[word] = first_translations;
      }
    }
  }
  else
  {
    for (auto it = first_dict.begin(); it != first_dict.end(); ++it)
    {
      if (second_dict.find(it->first) == second_dict.end())
      {
        result_dict.insert(*it);
      }
    }
  }
  dictionaries[new_dict_name] = result_dict;
}
