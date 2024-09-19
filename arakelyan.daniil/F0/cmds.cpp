#include "cmds.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <set>

void arakelyan::helpCommand(std::ostream &out)
{
  out << "LIST OF COMMANDS:\n";
  out << " - new <dictionary name> - создать новый словарь\n";
  out << " - delete <dictionary name> - удалить уже имеющийся словарь\n";
  out << " - add <dictionary name> <word> <translate> - добавить слово в уже";
  out << "имеющийся словарь\n";
  out << " - remove <dictionary name> <word> - удалить слово и его переводы (если они есть)";
  out << "из уже имеющегося словаря\n";
  out << " - merge <dictionary name1> <dictionary name2>- объединение двух словарей\n";
  out << " - move <dictionary name1> <key> <dictionary name2> - перенос ключа, с множеством";
  out << "его значений, из одного словаря, в другой\n";
  out << " - list - список всех словарей\n";
  out << " - size <dictionary name> - количество слов в выбранном словаре\n";
  out << " - print <dictionary name> - вывод ключей и значений из словаря\n";
  out << " - intersect <new dictionary name> <dictionary name 1> <dictionary name 2> - строит";
  out << "новый словарь, элементами которого являются повторяющиеся слова из";
  out << "двух указанных словарей\n";
  out << " - complement <new dictionary name> <dictionary name 1>";
  out << "<dictionary name 2> - строит";
  out << "новый словарь, элементами которого являются неповторяющиеся ключи\n";
  out << " - popular-aggregator <dictionary name> <top_{num}> - строит новый словарь с";
  out << "часто повторяющимися словами из другого N количества имеющихся словарей.";
  out << "вторым аргументом";
  out << "принимает кол-во популярных слов\n";
  out << " - rare-aggregator <dictionary name> <top {num}> - строит новый словарь с ";
  out << "редко встречающимися словами из другого N количества имеющихся словарей. вторым";
  out << "аргументом принимает кол-во непопулярных слов\n";
}

void arakelyan::addDictionary(std::istream &in, std::ostream &out,
                              dictionaries_t &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
    throw std::logic_error("<DICTIONARY ALREADY EXIST>");
  }
  std::map< std::string, std::vector< std::string > > newDictionary;
  dictionaries[name] = newDictionary;
  out << "YOU ADDED A NEW DICTIONARY \"" << name << "\".\n";
}

void arakelyan::deleteDictionary(std::istream &in, std::ostream &out,
                                 dictionaries_t &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  dictionaries.erase(name);
  out << "YOU DELETED A DICTIONARY \"" << name << "\".\n";
}

void arakelyan::addWord(std::istream &in, std::ostream &out, dictionaries_t &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }

  auto &userDict = dictionaries[name];
  std::string word = "";
  std::string translate = "";
  in >> word >> translate;
  if (userDict.find(word) != userDict.end())
  {
    auto status = std::find(userDict[word].begin(), userDict[word].end(), translate);
    if (status != userDict[word].end())
    {
      throw std::logic_error("<THIS TRANSLATION FOR THIS WORD ALREADY EXISTS>");
    }
    userDict[word].push_back(translate);
    out << "YOU ADDED A NEW TRANSLATION FOR WORD \""
      << word << "\" IN DICTIONARY \"" << name << "\".\n";
  }
  else
  {
    userDict[word].push_back(translate);
    out << "YOU ADDED A NEW WORD \"" << word << "\" AND IT'S TRANSLATION TO DICTIONARY \"" <<
      name << "\".\n";
  }
}

void arakelyan::removeWord(std::istream &in, std::ostream &out, dictionaries_t &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  auto &userDict = dictionaries[name];
  std::string word = "";
  in >> word;
  if (userDict.find(word) == userDict.end())
  {
    throw std::logic_error("<THAT WORD ISN'T IN THE DICTIONARY>");
  }
  userDict.erase(word);
  out << "YOU REMOVE \"" << word << "\" FROM YOU DICTIONARY \"" << name << "\".\n";
}

void arakelyan::wordTranslations(std::istream &in, std::ostream &out,
                                 const dictionaries_t &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  auto &userDict = dictionaries.at(name);
  std::string word = "";
  in >> word;
  if (userDict.find(word) == userDict.end())
  {
    throw std::logic_error("<THERE ARE NO WORD IN YOUR DICTIONARY>");
  }
  const auto translations = userDict.at(word);
  if (translations.empty())
  {
    throw std::logic_error("<THERE ARE NO TRANSLATIONS FOR THIS WORD>");
  }
  out << "TRANSLATIONS FOR \"" << word << "\": ";
  std::copy(translations.begin(), translations.end(),
            std::ostream_iterator< std::string >(out, " "));
  out << "\n";
}

void merge(std::map< std::string, std::vector< std::string > > &base,
           const std::pair< const std::string, std::vector< std::string > > &toMerge)
{
  const std::string &word = toMerge.first;
  const std::vector< std::string > &translations = toMerge.second;
  if (base.find(word) != base.end())
  {
    base[word].insert(base[word].end(), translations.begin(), translations.end());
  }
  else
  {
    base[word] = translations;
  }
}

void arakelyan::mergeDictionaries(std::istream &in, std::ostream &out,
                                  dictionaries_t &dictionaries)
{
  std::string name1 = "";
  std::string name2 = "";
  in >> name1 >> name2;
  if ((dictionaries.find(name1) == dictionaries.end()) ||
    (dictionaries.find(name2) == dictionaries.end()))
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH ONE OF THOSE NAMES>");
  }
  std::map< std::string, std::vector< std::string > > res;
  auto &dictOne = dictionaries[name1];
  const auto &dictTwo = dictionaries[name2];
  auto func = std::bind(merge, std::ref(dictOne), std::placeholders::_1);
  std::for_each(dictTwo.cbegin(), dictTwo.cend(), func);
  dictionaries.erase(name2);
  out << "MERGE DICTIONARY \"" << name2 << "\" INTO DICTIONARY \"" << name1 << "\".\n";
}

void arakelyan::moveWords(std::istream &in, std::ostream &out, dictionaries_t &dictionaries)
{
  std::string dictOneName = "";
  std::string word = "";
  std::string dictTwoName = "";
  in >> dictOneName >> word >> dictTwoName;
  if ((dictionaries.find(dictOneName) == dictionaries.end()) ||
    (dictionaries.find(dictTwoName) == dictionaries.end()))
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH ONE OF THOSE NAMES>");
  }
  auto &dictOne = dictionaries[dictOneName];
  auto &dictTwo = dictionaries[dictTwoName];
  if (dictOne.find(word) == dictOne.end())
  {
    dictOne[word] = dictTwo.find(word)->second;
  }
  else
  {
    dictOne[word].insert(dictOne[word].end(), dictTwo[word].begin(), dictTwo[word].end());
  }
  out << "MOVE WORD \"" << word << "\" FROM \"" << dictTwoName
    << "\" INTO \"" << dictOneName << "\".\n";
  dictTwo.erase(word);
}

void showName(std::ostream &out, const std::pair< std::string, std::map< std::string,
              std::vector< std::string > > >&dict)
{
  out << " - " << dict.first << '\n';
}

void arakelyan::showAllDictionariesNames(std::istream&, std::ostream &out,
                                         const dictionaries_t &dictionaries)
{
  if (dictionaries.empty())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARIES>");
  }
  out << "YOUR DICTIONARIES: \n";
  auto showFunc = std::bind(showName, std::ref(out), std::placeholders::_1);
  std::for_each(dictionaries.cbegin(), dictionaries.cend(), showFunc);
}

void arakelyan::getSizeOfDictionary(std::istream &in, std::ostream &out,
                                    const dictionaries_t &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  const auto &userDict = dictionaries.at(name);
  out << "DICTIONARY SIZE IS: " << userDict.size() << ".\n";
}

void showWordsAndTr(std::ostream &out,
                    const std::pair< std::string,
                    std::vector< std::string > > &wordEntry)
{
  out << " - " << wordEntry.first << " -> TRANSLATIONS: ";

  if (!wordEntry.second.empty())
  {
    std::copy(wordEntry.second.cbegin(), wordEntry.second.cend(),
              std::ostream_iterator<std::string>(out, "; "));
  }

  out << '\n';
}

void arakelyan::printTranslations(std::istream &in, std::ostream &out,
                                  const dictionaries_t &dictionaries)
{
  std::string dictName;
  in >> dictName;

  auto dictIt = dictionaries.find(dictName);
  if (dictIt == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }

  const auto &userDict = dictIt->second;
  if (userDict.empty())
  {
    throw std::logic_error("<YOUR DICTIONARY IS EMPTY>");
  }
  out << "DICTIONARY NAME \"" << dictIt->first << "\":\n";

  auto showWords = std::bind(showWordsAndTr, std::ref(out), std::placeholders::_1);
  std::for_each(userDict.cbegin(), userDict.cend(), showWords);
}

std::vector< std::string > mergeTranslations(const std::vector< std::string > &translations1,
                                             const std::vector< std::string > &translations2)
{
  std::vector< std::string > merged = translations1;

  for (const auto& translation : translations2)
  {
    if (std::find(merged.begin(), merged.end(), translation) == merged.end())
    {
      merged.push_back(translation);
    }
  }

  return merged;
}

std::set< std::string > getDictionaryKeys(const std::map< std::string,
                                          std::vector< std::string > > &dict)
{
  std::set< std::string > keys;
  for (const auto& pair : dict)
  {
    keys.insert(pair.first);
  }
  return keys;
}

void arakelyan::intersectDictionaries(std::istream &in, std::ostream &out,
                                      dictionaries_t &dictionaries)
{
  std::string newDictName = "";
  std::string dictName1 = "";
  std::string dictName2 = "";

  in >> newDictName >> dictName1 >> dictName2;

  if ((dictionaries.find(dictName1) == dictionaries.end()) ||
    (dictionaries.find(dictName2) == dictionaries.end()))
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH ONE OF THOSE NAMES>");
  }

  const auto &dict1 = dictionaries[dictName1];
  const auto &dict2 = dictionaries[dictName2];

  if (dict1.empty() || dict2.empty())
  {
    throw std::logic_error("<THERE ARE NO WORDS IN ONE OF YOUR DICTIONARIES>");
  }

  std::set< std::string > keys1 = getDictionaryKeys(dict1);
  std::set< std::string > keys2 = getDictionaryKeys(dict2);

  std::set< std::string > intersectKeys;
  std::set_intersection(keys1.begin(), keys1.end(), keys2.begin(), keys2.end(),
                        std::inserter(intersectKeys, intersectKeys.end()));

  std::map< std::string, std::vector< std::string > > newDict;

  for (const auto &key : intersectKeys)
  {
    const auto &translations1 = dict1.at(key);
    const auto &translations2 = dict2.at(key);

    newDict[key] = mergeTranslations(translations1, translations2);
  }

  dictionaries[newDictName] = newDict;

  out << "NEW DICTIONARY \"" << newDictName << "\" CREATED.\n";
}

bool keyNotInMap(const std::map<std::string, std::vector<std::string>>& dict,
                 const std::pair<const std::string, std::vector<std::string>>& pair)
{
  return dict.find(pair.first) == dict.end();
}

void arakelyan::complement(std::istream &in, std::ostream &, dictionaries_t &dictionaries)
{
  std::string newDictName = "";
  std::string dictOneName = "";
  std::string dictTwoName = "";

  in >> newDictName >> dictOneName >> dictTwoName;
  if (dictionaries.find(dictOneName) == dictionaries.end() ||
    dictionaries.find(dictTwoName) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH ONE OF THOSE NAMES>");
  }

  const auto &dictOne = dictionaries[dictOneName];
  const auto &dictTwo = dictionaries[dictTwoName];
  std::map< std::string, std::vector< std::string > > res;
  auto pr = std::bind(keyNotInMap, std::ref(dictOne), std::placeholders::_1);
  std::copy(dictOne.begin(), dictOne.end(), std::inserter(res, res.begin()));
  std::copy_if(dictTwo.begin(), dictTwo.end(), std::inserter(res, res.begin()), pr);
  dictionaries[newDictName] = res;
}
