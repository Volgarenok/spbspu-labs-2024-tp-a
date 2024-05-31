#include "Commands.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>

void kuzmina::showHelp(std::ostream& out)
{
  out << "Available commands:\n";
  out << " - addWord <dict> <word> - adds word\n";
  out << " - addTranslation <dict> <word> <translation> - adds translation\n";
  out << " - searchWord <dict> <word> - searches for word\n";
  out << " - searchTranslation <dict> <word> <translation> - searches for translation\n";
  out << " - deleteWord <dict> <word> - deletes word\n";
  out << " - deleteWord <dict> <word> <translation> - deletes translation\n";
  out << " - findSynonyms <dict> <word> - finds synonyms according to translations\n";
  out << " - countWords <dict> <prefix> - counts words starting with prefix\n";
  out << " - intersect <dictR> <dict1> <dict2> - dictR is an intersection of dict1 and dict2\n";
  out << " - subtract <dictR> <dict1> <dict2> - dictR is a difference between dict1 and dict2\n";
  out << " - merge <dict1> <merge2> - merges dict2 into dict1 both words and translations\n";
  out << " - print <dict> - prints out all the content\n";
}

bool hasTranslation(const std::vector< std::string >& data, const std::string& translation)
{
  return std::find(data.cbegin(), data.cend(), translation) != data.cend();
}

void kuzmina::addWord(std::istream& in, allDicts& dicts)
{
  std::string dictName, word;
  in >> dictName >> word;

  Dict& dict = dicts.at(dictName);

  if (dict.count(word))
  {
    throw std::logic_error("This word is already in the dictionary");
  }

  dict[word] = std::vector< std::string >{};
}

void kuzmina::addTranslation(std::istream& in, allDicts& dicts)
{
  std::string dictName, word, translation;
  in >> dictName >> word >> translation;

  Dict& dict = dicts.at(dictName);

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  if (hasTranslation(dict.at(word), translation))
  {
    throw std::logic_error("This word already has such translation");
  }

  dict.at(word).push_back(translation);
  std::sort(dict.at(word).begin(), dict.at(word).end());
}

void kuzmina::searchWord(std::istream& in, std::ostream& out, const allDicts& dicts)
{
  std::string dictName, word;
  in >> dictName >> word;

  const Dict& dict = dicts.at(dictName);

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  out << word << ": ";

  if (dict.at(word).size() == 0)
  {
    std::cout << "(no translations added yet)";
  }
  else
  {
    using output_it_t = std::ostream_iterator< std::string >;
    std::copy(dict.at(word).cbegin(), dict.at(word).cend(), output_it_t{ out, " " });
  }
}

void kuzmina::searchTranslation(std::istream& in, std::ostream& out, const allDicts& dicts)
{
  std::string dictName, translation;
  in >> dictName >> translation;

  const Dict& dict = dicts.at(dictName);

  std::vector< std::string > words;

  for (auto word_i: dict)
  {
    if (hasTranslation(word_i.second, translation))
    {
      words.push_back(word_i.first);
    }
  }

  if (words.size() == 0)
  {
    throw std::logic_error("No such translation");
  }
  else
  {
    out << translation << ": ";

    using output_it_t = std::ostream_iterator< std::string >;
    std::copy(words.cbegin(),words.cend(), output_it_t{ out, " " });
  }
}

void kuzmina::deleteWord(std::istream& in, allDicts& dicts)
{
  std::string dictName, word;
  in >> dictName >> word;

  Dict& dict = dicts.at(dictName);

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  dict.erase(word);
}

void kuzmina::deleteTranslation(std::istream& in, allDicts& dicts)
{
  std::string dictName, word, translation;
  in >> dictName >> word >> translation;

  Dict& dict = dicts.at(dictName);

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  if (!hasTranslation(dict.at(word), translation))
  {
    throw std::logic_error("No such translation");
  }

  auto translationIt = std::find(dict.at(word).cbegin(), dict.at(word).cend(), translation);
  dict.at(word).erase(translationIt);
}

void kuzmina::findSynonyms(std::istream& in, std::ostream& out, const allDicts& dicts)
{
  std::string dictName, word;
  in >> dictName >> word;

  const Dict& dict = dicts.at(dictName);

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  std::vector< std::string > synonyms;

  for (auto translation_i: dict.at(word))
  {
    for (auto word_i: dict)
    {
      if (hasTranslation(word_i.second, translation_i) && word_i.first != word)
      {
        synonyms.push_back(word_i.first);
      }
    }
  }

  out << word << ": ";

  if (synonyms.size() == 0)
  {
    std::cout << "(no synonyms)";
  }
  else
  {
    using output_it_t = std::ostream_iterator< std::string >;
    std::copy(synonyms.cbegin(), synonyms.cend(), output_it_t{ out, " " });
  }
}

bool startsWith(const std::pair< std::string, std::vector< std::string > >& word, const std::string& prefix)
{
  size_t len = prefix.length();

  return word.first.compare(0, len, prefix, 0, len) == 0;
}

void kuzmina::countWords(std::istream& in, std::ostream& out, const allDicts& dicts)
{
  std::string dictName, prefix;
  in >> dictName >> prefix;

  const Dict& dict = dicts.at(dictName);

  using namespace std::placeholders;
  out << std::count_if(dict.cbegin(), dict.cend(), std::bind(startsWith, _1, prefix));
}

void kuzmina::intersect(std::istream& in, allDicts& dicts)
{
  std::string dictName1, dictName2, dictNameR;
  in >> dictNameR >> dictName1 >> dictName2;

  Dict& dict1 = dicts.at(dictName1);
  Dict& dict2 = dicts.at(dictName2);
  Dict& dictR = dicts.at(dictNameR);

  for (auto word_i: dict1)
  {
    if (dict2.count(word_i.first))
    {
      std::vector< std::string > trnslR;
      std::vector< std::string > trnsl1 = dict1.at(word_i.first);
      std::vector< std::string > trnsl2 = dict2.at(word_i.first);

      std::set_intersection(trnsl1.cbegin(), trnsl1.cend(), trnsl2.cbegin(), trnsl2.cend(), std::back_inserter(trnslR));

      dictR[word_i.first] = trnslR;
    }
  }

  if (dictR.empty())
  {
    throw std::logic_error("No mutual words!");
  }
}

void kuzmina::subtract(std::istream& in, allDicts& dicts)
{
  std::string dictName1, dictName2, dictNameR;
  in >> dictNameR >> dictName1 >> dictName2;

  Dict& dict1 = dicts.at(dictName1);
  Dict& dict2 = dicts.at(dictName2);
  Dict& dictR = dicts.at(dictNameR);

  for (auto word_i: dict1)
  {
    if (dict2.count(word_i.first))
    {
    std::vector< std::string > trnslR;
    std::vector< std::string > trnsl1 = dict1.at(word_i.first);
    std::vector< std::string > trnsl2 = dict2.at(word_i.first);

    std::set_difference(trnsl1.cbegin(), trnsl1.cend(), trnsl2.cbegin(), trnsl2.cend(), std::back_inserter(trnslR));

    dictR[word_i.first] = trnslR;
    }
    else
    {
      dictR[word_i.first] = dict1.at(word_i.first);
    }
  }

  if (dictR.empty())
  {
    throw std::logic_error("They were same...");
  }
}

void kuzmina::merge(std::istream& in, allDicts& dicts)
{
  std::string dictName1, dictName2;
  in >> dictName1 >> dictName2;

  Dict& dict1 = dicts.at(dictName1);
  Dict& dict2 = dicts.at(dictName2);
  bool merged = 0;

  for (auto word_i: dict2)
  {
    if (dict1.count(word_i.first))
    {
      std::vector< std::string > trnslM;
      std::vector< std::string > trnsl1 = dict1.at(word_i.first);
      std::vector< std::string > trnsl2 = dict2.at(word_i.first);

      std::set_difference(trnsl2.cbegin(), trnsl2.cend(), trnsl1.cbegin(), trnsl1.cend(), std::back_inserter(trnslM));

      dict1.at(word_i.first).clear();
      std::merge(trnsl1.cbegin(), trnsl1.cend(), trnslM.cbegin(), trnslM.cend(), std::back_inserter(dict1.at(word_i.first)));

      merged = 1;
    }
    else
    {
      dict1[word_i.first] = dict2.at(word_i.first);
    }
  }

  if (!merged)
  {
    throw std::logic_error("They were same...");
  }
}

void kuzmina::print(std::istream& in, std::ostream& out, const allDicts& dicts)
{
  std::string dictName;
  in >> dictName;

  const Dict& dict = dicts.at(dictName);
  using output_it_t = std::ostream_iterator< std::string >;

  for (auto word_i: dict)
  {
    out << word_i.first << ": ";

    if (word_i.second.size() == 0)
    {
      out << "(no translations added yet)";
    }
    else
    {
      std::copy(word_i.second.cbegin(), word_i.second.cend(), output_it_t{ out, " " });
    }

    out << '\n';
  }
}
