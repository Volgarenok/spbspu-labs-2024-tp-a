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

bool hasTranslation(const kuzmina::Record& data, std::string& translation)
{
  return std::find(data.second.cbegin(), data.second.cend(), translation) != data.second.cend();
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

  if (hasTranslation({ word, dict.at(word) }, translation))
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

std::string getKey(const kuzmina::Record& data)
{
  return data.first;
}

void kuzmina::searchTranslation(std::istream& in, std::ostream& out, const allDicts& dicts)
{
  std::string dictName, translation;
  in >> dictName >> translation;

  const Dict& dict = dicts.at(dictName);
  Dict toProcess;

  using namespace std::placeholders;
  std::copy_if(dict.cbegin(), dict.cend(), std::inserter(toProcess, toProcess.end()), std::bind(hasTranslation, _1, translation));

  if (toProcess.empty())
  {
    throw std::logic_error("No such translation");
  }
  else
  {
    out << translation << ": ";

    std::vector< std::string > words;
    std::transform(toProcess.begin(), toProcess.end(), std::back_inserter(words), std::bind(getKey, _1));

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

  if (!hasTranslation({ word, dict.at(word) }, translation))
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
  Dict toProcess;

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  using namespace std::placeholders;

  //std::for_each(dict.at(word).begin(), dict.at(word).end(), );
  for (auto translation_i: dict.at(word))
  {
    std::copy_if(dict.begin(), dict.end(), std::inserter(toProcess, toProcess.end()), std::bind(hasTranslation, _1, translation_i));
  }
  toProcess.erase(word);

  out << word << ": ";

  if (toProcess.empty())
  {
    throw std::logic_error("(no synonyms)");
  }
  else
  {
    std::vector< std::string > synonyms;
    std::transform(toProcess.begin(), toProcess.end(), std::back_inserter(synonyms), std::bind(getKey, _1));

    using output_it_t = std::ostream_iterator< std::string >;
    std::copy(synonyms.cbegin(), synonyms.cend(), output_it_t{ out, " " });
  }
}

bool startsWith(const kuzmina::Record& word, const std::string& prefix)
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

bool haveIntersection(kuzmina::Dict& dict2, const kuzmina::Record& data)
{
  return dict2.count(data.first);
}

kuzmina::Record getIntersection(kuzmina::Dict& dict1, kuzmina::Dict& dict2, const kuzmina::Record& data)
{
  std::vector< std::string > trnslR;
  std::vector< std::string > trnsl1 = dict1.at(data.first);
  std::vector< std::string > trnsl2 = dict2.at(data.first);

  std::set_intersection(trnsl1.cbegin(), trnsl1.cend(), trnsl2.cbegin(), trnsl2.cend(), std::back_inserter(trnslR));

  return { data.first, trnslR };
}

void kuzmina::intersect(std::istream& in, allDicts& dicts)
{
  std::string dictName1, dictName2, dictNameR;
  in >> dictNameR >> dictName1 >> dictName2;

  Dict& dict1 = dicts.at(dictName1);
  Dict& dict2 = dicts.at(dictName2);
  Dict& dictR = dicts.at(dictNameR);

  dictR.clear();
  Dict temp;

  using namespace std::placeholders;
  std::copy_if(dict1.begin(), dict1.end(), std::inserter(temp, temp.end()), std::bind(haveIntersection, dict2, _1));
  std::transform(temp.begin(), temp.end(), std::inserter(dictR, dictR.end()), std::bind(getIntersection, temp, dict2, _1));

  if (dictR.empty())
  {
    throw std::logic_error("No mutual words");
  }
}

kuzmina::Record getDifference(kuzmina::Dict& dict1, kuzmina::Dict& dict2, const kuzmina::Record& data)
{
  if (dict2.count(data.first))
  {
    std::vector< std::string > trnslR;
    std::vector< std::string > trnsl1 = dict1.at(data.first);
    std::vector< std::string > trnsl2 = dict2.at(data.first);

    std::set_difference(trnsl1.cbegin(), trnsl1.cend(), trnsl2.cbegin(), trnsl2.cend(), std::back_inserter(trnslR));

    return { data.first, trnslR };
  }
  return { data.first, dict1.at(data.first) };
}

void kuzmina::subtract(std::istream& in, allDicts& dicts)
{
  std::string dictName1, dictName2, dictNameR;
  in >> dictNameR >> dictName1 >> dictName2;

  Dict& dict1 = dicts.at(dictName1);
  Dict& dict2 = dicts.at(dictName2);
  Dict& dictR = dicts.at(dictNameR);

  dictR.clear();
  Dict temp;

  using namespace std::placeholders;
  std::transform(dict1.begin(), dict1.end(), std::inserter(dictR, dictR.end()), std::bind(getDifference, dict1, dict2, _1));

  if (dictR.empty())
  {
    throw std::logic_error("They were same...");
  }
}

kuzmina::Record getMerge(kuzmina::Dict& dict1, kuzmina::Dict& dict2, const kuzmina::Record& data)
{
  if (dict1.count(data.first))
  {
    std::vector< std::string > trnslM;
    std::vector< std::string > trnsl1 = dict1.at(data.first);
    std::vector< std::string > trnsl2 = dict2.at(data.first);

    std::set_difference(trnsl2.cbegin(), trnsl2.cend(), trnsl1.cbegin(), trnsl1.cend(), std::back_inserter(trnslM));

    dict1.at(data.first).clear();
    std::merge(trnsl1.cbegin(), trnsl1.cend(), trnslM.cbegin(), trnslM.cend(), std::back_inserter(dict1.at(data.first)));

    return { data.first, dict1.at(data.first) };
  }
  else
  {
    return { data.first, dict2.at(data.first) };
  }
}

bool hasNotKey(kuzmina::Dict& dict, const kuzmina::Record data)
{
  return !dict.count(data.first);
}

void kuzmina::merge(std::istream& in, allDicts& dicts)
{
  std::string dictName1, dictName2;
  in >> dictName1 >> dictName2;

  Dict& dict1 = dicts.at(dictName1);
  Dict& dict2 = dicts.at(dictName2);

  Dict temp;

  using namespace std::placeholders;
  std::transform(dict2.cbegin(), dict2.cend(), std::inserter(temp, temp.end()), std::bind(getMerge, dict1, dict2, _1));

  if (temp == dict1)
  {
    throw std::logic_error("They were same...");
  }

  std::copy_if(dict1.begin(), dict1.end(), std::inserter(temp, temp.end()), std::bind(hasNotKey, temp, _1));
  dict1 = temp;
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
