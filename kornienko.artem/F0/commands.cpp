#include "commands.hpp"
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <numeric>

void kornienko::help(std::ostream & out)
{
  out << "Система команд:\n";
  out << "1. CREATE < dictionary >\n";
  out << "Создает пустой словарь dictionary. Если словарь с таким именем уже есть,\n";
  out << "то вывод сообщения <ALREADY EXISTS>\n";
  out << "2. DELETE < dictionary >\n";
  out << "Удаляет словарь dictionary. Если такого словаря не существует,\n";
  out << "то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "3. ADDWORD < dictionary > < word >\n";
  out << "Добавляется слово word в словарь dictionary.\n";
  out << "Если такое слово уже есть в словаре, то вывод сообщения <ALREADY ADDED>\n";
  out << "Если слово задано некорректно, то вывод сообщения <INVALID WORD>.\n";
  out << "Если такого словаря не существует,\n";
  out << "то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "4. ADDTRANLATION < dictionary > < word > < translation >\n";
  out << "Добавляется перевод translation к слову word в словарь dictionary.\n";
  out << "Если перевод такого слова уже есть в словаре,\n";
  out << "то вывод сообщения <ALREADY ADDED>\n";
  out << "Если слово задано некорректно, то вывод сообщения <INVALID WORD>\n";
  out << "Если перевод слова задан некорректно, то вывод сообщения <INVALID TRANSLATION>\n";
  out << "Если такого словаря не существует,\n";
  out << "то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "5. DELETEWORD < dictionary > < word >";
  out << "Удаляется слово word из словаря dictionary.\n";
  out << "Если такого слова нет в словаре, то вывод сообщения < WORD DOESN’T EXIST >.\n";
  out << "Если слово задано некорректно, то вывод сообщения .\n";
  out << " Если такого словаря не существует, то вывод <DICTIONARY DOESN’T EXIST>.\n";
  out << "6. MERGE < newDictionary > < dictionary1 > < dictionary2 >\n";
  out << "Создает новый словарь newDictionary, в котором содержатся все слова из\n";
  out << "словарей dictionary1 и dictionary2.\n";
  out << "Если какого-то из словарей  не существует,\n";
  out << "то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "7. INTERSECT < newDictionary > < dictionary1 > < dictionary2  >\n";
  out << "Создает новый словарь newDictionary, в который добавляются слова,\n";
  out << "которые содержатся сразу в двух словарях: dictionary1, dictionary2\n";
  out << "Если какого-то из словарей не существует,\n";
  out << "то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "8. DIFFERENCE < newDictionary > < dictionary1 > < dictionary2 >\n";
  out << "Создает новый словарь newDictionary, в который  добавляются слова,\n";
  out << "которые содержатся только водном из двух словарей: dictionary1 и dictionary2.\n";
  out << "Если какого-то из словарей не существует,\n";
  out << "то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "9. LIMIT < newDictionary > < dictionary > < word1 > <  word2 >\n";
  out << "Создает новый словарь newDictionary,\n";
  out << "в который добавляются слова начиная с word1 до word2.\n";
  out << "Если какого-то из слов  нет в словаре то вывод сообщения <INCORRECT WORD>\n";
  out << "Если такого словаря не существует, то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "10. OUTPUT < dictionary >\n";
  out << "Выводит все слова из словаря dictionary с их переводами.\n";
  out << "Если такого словаря не существует, то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "11. GETTRANSLATION < dictionary > < word >\n";
  out << "Выводится  перевод к слову word из словаря dictionary.\n";
  out << "Если слово задано некорректно, то вывод сообщения <INCORRECT WORD>\n";
  out << "Если такого словаря не  существует, то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
  out << "12. NOTTRANSLATED < dictionary >\n";
  out << "Выводит все слова из словаря dictionary у которых нет перевода.\n";
  out << "Если такого словаря не существует,то вывод сообщения <DICTIONARY DOESN’T EXIST>.\n";
}

using mapDict = std::map< std::string, kornienko::Dictionary >;
void kornienko::createDictionary(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string newName;
  in >> newName;
  if (dictionaries.find(newName) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXIST>\n");
  }
  dictionaries[newName];
}

void kornienko::deleteDictionary(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string name;
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
     dictionaries.erase(name);
  }
  else
  {
     throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
}

bool isWord(const std::string & word)
{
  return std::all_of(word.cbegin(), word.cend(), isalpha);
}

void kornienko::addWord(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  if (!isWord(word))
  {
    throw std::logic_error("<INCORRECT WORD>\n");
  }
  if (dictionaries.find(dictName) != dictionaries.end())
  {
    if (dictionaries[dictName].dictionary_.find(word) != dictionaries[dictName].dictionary_.end())
    {
      throw std::logic_error("<WORD ALREADY EXISTS>\n");
    }
    else
    {
      dictionaries[dictName].dictionary_[word];
    }
  }
  else
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
}

void kornienko::deleteWord(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  if (dictionaries.find(dictName) != dictionaries.end())
  {
    if (dictionaries[dictName].dictionary_.find(word) != dictionaries[dictName].dictionary_.end())
    {
      dictionaries[dictName].dictionary_.erase(word);
    }
    else
    {
      throw std::logic_error("<WORD DOESN’T EXIST>\n");
    }
  }
  else
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
}

void kornienko::addTranslation(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string dictName;
  std::string word;
  std::string translation;
  in >> dictName >> word >> translation;
  if (!isWord(word))
  {
    throw std::logic_error("<INCORRECT WORD>\n");
  }
  if (!isWord(translation))
  {
    throw std::logic_error("<INCORRECT TRANSLATION>\n");
  }
  if (dictionaries.find(dictName) != dictionaries.end())
  {
    if (dictionaries[dictName].dictionary_.find(word) != dictionaries[dictName].dictionary_.end())
    {
      auto dictWord = dictionaries[dictName].dictionary_[word];
      if (std::find(dictWord.cbegin(), dictWord.cend(), translation) == dictWord.end())
      {
        dictionaries[dictName].dictionary_[word].push_back(translation);
        sort(dictionaries[dictName].dictionary_[word].begin(),
         dictionaries[dictName].dictionary_[word].end());
      }
      else
      {
        throw std::logic_error("<ALREADY ADDED>\n");
      }
    }
    else
    {
      throw std::logic_error("<INCORRECT WORD>\n");
    }
  }
  else
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
}

void kornienko::output(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string name;
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
     throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  out << name << " words:\n";
  for (const auto& words : dictionaries[name].dictionary_)
  {
    out << words.first << ": ";
    for (const auto& trans : words.second)
    {
      out << trans << " ";
    }
    out << "\n";
  }
}

void kornienko::merge(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  if (dictionaries.find(newName) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXIST>\n");
  }
  if (dictionaries.find(name1) == dictionaries.end() || dictionaries.find(name2) == dictionaries.end())
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  auto itDict1 = dictionaries[name1].dictionary_.begin();
  auto itDict2 = dictionaries[name2].dictionary_.begin();
  while (itDict1 != dictionaries[name1].dictionary_.end() &&
   itDict2 != dictionaries[name2].dictionary_.end())
  {
    if ((*itDict1).first < (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict1).first] = (*itDict1).second;
      ++itDict1;
    }
    else if ((*itDict1).first > (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict2).first] = (*itDict2).second;
      ++itDict2;
    }
    else
    {
      auto beg1 = dictionaries[newName].dictionary_[(*itDict1).first].begin();
      auto newDictionary = dictionaries[newName].dictionary_;
      newDictionary[(*itDict1).first].insert(beg1, (*itDict1).second.begin(),
       (*itDict1).second.end());
      auto beg2 = dictionaries[newName].dictionary_[(*itDict2).first].begin();
      newDictionary[(*itDict1).first].insert(beg2, (*itDict2).second.begin(),
       (*itDict2).second.end());
      std::sort(newDictionary[(*itDict1).first].begin(), newDictionary[(*itDict1).first].end());
      ++itDict1;
      ++itDict2;
    }
  }
  if (itDict1 != dictionaries[name1].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict1, dictionaries[name1].dictionary_.end());
  }
  else if (itDict2 != dictionaries[name2].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict2, dictionaries[name2].dictionary_.end());
  }
}

void kornienko::intersect(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  if (dictionaries.find(newName) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXIST>\n");
  }
  if (dictionaries.find(name1) == dictionaries.end() ||
   dictionaries.find(name2) == dictionaries.end())
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  auto itDict1 = dictionaries[name1].dictionary_.begin();
  auto itDict2 = dictionaries[name2].dictionary_.begin();
  while (itDict1 != dictionaries[name1].dictionary_.end() &&
   itDict2 != dictionaries[name2].dictionary_.end())
  {
    if ((*itDict1).first < (*itDict2).first)
    {
      ++itDict1;
    }
    else if ((*itDict1).first > (*itDict2).first)
    {
      ++itDict2;
    }
    else
    {
      auto beg1 = dictionaries[newName].dictionary_[(*itDict1).first].begin();
      auto newDictionary = dictionaries[newName].dictionary_;
      newDictionary[(*itDict1).first].insert(beg1, (*itDict1).second.begin(), (*itDict1).second.end());
      auto beg2 = dictionaries[newName].dictionary_[(*itDict2).first].begin();
      newDictionary[(*itDict1).first].insert(beg2, (*itDict2).second.begin(), (*itDict2).second.end());
      std::sort(newDictionary[(*itDict1).first].begin(), newDictionary[(*itDict1).first].end());
      ++itDict1;
      ++itDict2;
    }
  }
}

void kornienko::difference(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  if (dictionaries.find(newName) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXIST>\n");
  }
  if (dictionaries.find(name1) == dictionaries.end() || dictionaries.find(name2) == dictionaries.end())
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  auto itDict1 = dictionaries[name1].dictionary_.begin();
  auto itDict2 = dictionaries[name2].dictionary_.begin();
  while (itDict1 != dictionaries[name1].dictionary_.end() &&
   itDict2 != dictionaries[name2].dictionary_.end())
  {
    if ((*itDict1).first < (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict1).first] = (*itDict1).second;
      ++itDict1;
    }
    else if ((*itDict1).first > (*itDict2).first)
    {
      dictionaries[newName].dictionary_[(*itDict2).first] = (*itDict2).second;
      ++itDict2;
    }
    else
    {
      ++itDict1;
      ++itDict2;
    }
  }
  if (itDict1 != dictionaries[name1].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict1, dictionaries[name1].dictionary_.end());
  }
  else if (itDict2 != dictionaries[name2].dictionary_.end())
  {
    dictionaries[newName].dictionary_.insert(itDict2, dictionaries[name2].dictionary_.end());
  }
}

void kornienko::limit(std::istream & in, std::ostream &, mapDict & dictionaries)
{
  std::string newName;
  std::string name;
  std::string start;
  std::string end;
  in >> newName >> name >> start >> end;
  if (dictionaries.find(newName) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXIST>\n");
  }
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  auto iter1 = dictionaries[name].dictionary_.find(start);
  auto iter2 = ++dictionaries[name].dictionary_.find(end);
  if (iter1 == dictionaries[name].dictionary_.end() ||
   iter2 == dictionaries[name].dictionary_.end())
  {
    throw std::logic_error("<INCORRECT WORD>\n");
  }
  dictionaries[newName].dictionary_.insert(iter1, iter2);
}

void kornienko::getTranslation(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string name;
  std::string word;
  in >> name >> word;
  if (dictionaries.find(name) == dictionaries.end())
  {
     throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  if (dictionaries[name].dictionary_.find(word) == dictionaries[name].dictionary_.end())
  {
    throw std::logic_error("<INCORRECT WORD\n>");
  }
  for (const auto& trans : (*dictionaries[name].dictionary_.find(word)).second)
  {
    out << trans << " ";
  }
  out << "\n";
}

void kornienko::notTranslated(std::istream & in, std::ostream & out, mapDict & dictionaries)
{
  std::string name;
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
     throw std::logic_error("<DICTIONARY DOESN’T EXIST>\n");
  }
  out << name << " words without translation:\n";
  for (const auto& word : dictionaries[name].dictionary_)
  {
    if (word.second.empty())
    {
      out << word.first << " ";
    }
  }
  out << "\n";
}
