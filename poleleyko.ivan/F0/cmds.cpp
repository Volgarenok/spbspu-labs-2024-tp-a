#include "cmds.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>

void poleleyko::addDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }
  std::map< std::string, std::vector< std::string > > new_dict = {};
  dictionaries[name] = new_dict;
}

void poleleyko::deleteDictionary(std::istream& in,
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

void poleleyko::addWord(std::istream& in,
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

void poleleyko::removeWord(std::istream& in,
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
  if (needed_dict.find(word) == needed_dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  needed_dict.erase(word);
}

void poleleyko::translate(std::ostream& out,
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

void mergeEntry(std::map< std::string, std::vector< std::string > >& first,
    const std::pair< const std::string, std::vector< std::string > >& entry)
{
  const std::string& key = entry.first;
  const std::vector< std::string >& values = entry.second;

  if (first.find(key) != first.end())
  {
    first[key].insert(first[key].end(), values.begin(), values.end());
  }
  else
  {
    first[key] = values;
  }
}

void poleleyko::mergeDictionaries(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string first_name = "";
  std::string second_name = "";
  std::map< std::string, std::vector< std::string > > result = {};
  in >> first_name >> second_name;
  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& first = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second = dictionaries[second_name];
  std::for_each(second.cbegin(), second.cend(), std::bind(mergeEntry, std::ref(first), std::placeholders::_1));
}

bool isCommonTranslation(const std::string& translation, const std::vector< std::string >& second_translations)
{
  return std::find(second_translations.begin(), second_translations.end(), translation) != second_translations.end();
}

void insertCommonTranslations(std::map< std::string, std::vector< std::string > >& result_dict,
    const std::pair< const std::string, std::vector< std::string > >& entry,
    const std::map< std::string, std::vector< std::string > >& second_dict)
{
  const std::string& word = entry.first;
  const std::vector< std::string >& first_translations = entry.second;

  auto it2 = second_dict.find(word);
  if (it2 != second_dict.end())
  {
    const std::vector< std::string >& second_translations = it2->second;
    std::vector< std::string > common_translations;
    std::copy_if(first_translations.begin(), first_translations.end(), std::back_inserter(common_translations),
        std::bind(isCommonTranslation, std::placeholders::_1, std::cref(second_translations)));
    if (!common_translations.empty())
    {
      result_dict[word] = common_translations;
    }
  }
}

void poleleyko::getIntersection(std::istream& in,
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
  using namespace std::placeholders;
  std::for_each(first_dict.begin(), first_dict.end(),
      std::bind(insertCommonTranslations, std::ref(result_dict), _1, std::cref(second_dict)));
  dictionaries[new_dict_name] = result_dict;
}

bool keyNotInMap(const std::map< std::string, std::vector< std::string > >& map, const std::string& key)
{
  return map.find(key) == map.end();
}

void poleleyko::getCombining(std::istream& in,
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
  auto pred = std::bind(keyNotInMap, std::cref(result_dict), std::placeholders::_1);
  std::copy(first_dict.begin(), first_dict.end(), std::inserter(result_dict, result_dict.end()));
  std::copy_if(second_dict.begin(), second_dict.end(), std::inserter(result_dict, result_dict.end()),
      [&pred](const auto& entry) {
        return pred(entry.first);
      });

  dictionaries[new_dict_name] = result_dict;
}

std::vector< std::string > computeDifference(const std::vector< std::string >& v1, const std::vector< std::string >& v2)
{
  std::vector< std::string > difference;
  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(difference));
  return difference;
}

void handleTranslationComparison(const std::map< std::string, std::vector< std::string > >& first_dict,
    const std::map< std::string, std::vector< std::string > >& second_dict,
    std::map< std::string, std::vector< std::string > >& result_dict)
{
  std::for_each(first_dict.begin(), first_dict.end(), [&](const auto& pair) {
    auto second_it = second_dict.find(pair.first);
    if (second_it != second_dict.end())
    {
      const auto& second_translations = second_it->second;
      std::vector< std::string > diff = computeDifference(pair.second, second_translations);
      if (!diff.empty())
      {
        result_dict[pair.first] = diff;
      }
    }
    else
    {
      result_dict[pair.first] = pair.second;
    }
  });
}

void poleleyko::getDifference(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string new_dict_name = "";
  std::string first_name = "";
  std::string second_name = "";
  std::string comparison_type = "";
  in >> new_dict_name >> first_name >> second_name >> comparison_type;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& first_dict = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second_dict = dictionaries[second_name];
  std::map< std::string, std::vector< std::string > > result_dict = {};

  if (comparison_type == "translation")
  {
    handleTranslationComparison(first_dict, second_dict, result_dict);
  }
  else
  {
    std::set_difference(first_dict.begin(), first_dict.end(), second_dict.begin(), second_dict.end(),
        std::inserter(result_dict, result_dict.end()),
        [](const auto& lhs, const auto& rhs) {
          return lhs.first < rhs.first;
        });
  }
  dictionaries[new_dict_name] = result_dict;
}