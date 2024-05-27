#include "commands.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include "dictionary.hpp"

namespace demidenko
{
  const char* ERROR_MESSAGE = "Error accured\n";
}
void demidenko::doCheckCmd(std::istream& in, std::ostream& out)
{
  std::string fileName;
  in >> fileName;
  std::ifstream inFile(fileName);
  Dictionary::Record record;
  while (!inFile.eof())
  {
    in >> record;
    if (in.fail())
    {
      out << "Incorrect file\n";
      break;
    }
  }
  out << "Correct file\n";
}
void demidenko::doAddCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string dictionaryName;
  Dictionary::Record record;
  in >> dictionaryName >> record;
  if (in.fail() || !dictionaries.at(dictionaryName).addRecord(std::move(record)))
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::doRemoveCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string dictionaryName;
  Dictionary::Record record;
  in >> dictionaryName >> record;
  bool isCorrectInput = !record.first.empty() && (record.second.empty() || !in.fail());
  in.clear();
  if (!isCorrectInput || !dictionaries.at(dictionaryName).removeRecord(record))
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::doSaveCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string dictionaryName;
  std::string fileName;
  std::getline(in, dictionaryName, ' ');
  std::getline(in, fileName);
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  in >> std::ws;
  std::ofstream outFile;
  const Dictionary& dictionary = dictionaries.at(dictionaryName);
  if (fileName.empty())
  {
    outFile.open(dictionaryName);
  }
  else
  {
    outFile.open(fileName);
  }
  outFile << dictionary;
}
void demidenko::doLoadCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string dictionaryName;
  std::string fileName;
  std::getline(in, dictionaryName, ' ');
  std::getline(in, fileName);
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  in >> std::ws;
  std::ifstream inFile;
  if (dictionaryName.empty())
  {
    inFile.open(dictionaryName);
  }
  else
  {
    inFile.open(fileName);
  }
  Dictionary dictionary;
  inFile >> dictionary;
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  dictionaries[dictionaryName] = dictionary;
}
void demidenko::doListCmd(std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  for (auto& dictionary : dictionaries)
  {
    out << dictionary.first << '\n';
  }
}
void demidenko::doTranslateCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  std::string word;
  std::string dictionaryName;
  std::getline(in, word, ' ');
  std::getline(in, dictionaryName);
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  in >> std::ws;
  if (dictionaryName.empty())
  {
    in.clear();
    for (auto& dictionary : dictionaries)
    {
      dictionary.second.translate(word, out);
    }
  }
  else
  {
    dictionaries[dictionaryName].translate(word, out);
  }
}
void demidenko::doSearchCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  std::string translation;
  std::string dictionaryName;
  std::getline(in, translation, ' ');
  std::getline(in, dictionaryName);
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  in >> std::ws;
  if (dictionaryName.empty())
  {
    in.clear();
    for (auto& dictionary : dictionaries)
    {
      dictionary.second.search(translation, out);
    }
  }
  else
  {
    dictionaries[dictionaryName].search(translation, out);
  }
}
void demidenko::doPrefixCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  std::string prefix;
  std::string dictionaryName;
  std::getline(in, prefix, ' ');
  std::getline(in, dictionaryName);
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  in >> std::ws;
  if (dictionaryName.empty())
  {
    in.clear();
    for (auto& dictionary : dictionaries)
    {
      dictionary.second.prefix(prefix, out);
    }
  }
  else
  {
    dictionaries[dictionaryName].prefix(prefix, out);
  }
}
void demidenko::doMergeCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string firstDictionary;
  std::string secondDictionary;
  std::string thirdDictionary;
  in >> firstDictionary >> secondDictionary >> thirdDictionary;
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  dictionaries[thirdDictionary] = dictionaries.at(firstDictionary);
  dictionaries[thirdDictionary].merge(dictionaries.at(secondDictionary));
}
void demidenko::doExcludeCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string firstDictionary;
  std::string secondDictionary;
  std::string thirdDictionary;
  in >> firstDictionary >> secondDictionary >> thirdDictionary;
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  dictionaries[thirdDictionary] = dictionaries.at(firstDictionary);
  dictionaries[thirdDictionary].exclude(dictionaries.at(secondDictionary));
}
void demidenko::doSplitCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string firstDictionary;
  std::string word;
  std::string secondDictionary;
  std::string thirdDictionary;
  in >> firstDictionary >> word >> secondDictionary >> thirdDictionary;
  if (in.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  dictionaries.at(firstDictionary).split(word, dictionaries[secondDictionary], dictionaries[thirdDictionary]);
}
void demidenko::doHelpCmd(std::ostream& out)
{
  out << "Параметры командной строки:\n";
  out << "<dict> [file] запуск с загрузкой словаря с именем <dict> из файла [file], если\n";
  out << "указан. Иначе загрузить из файла <dict>\n";
  out << "--help вывод справки\n";
  out << "--check <file> проверка корректности словаря в файле <file>\n";
  out << '\n';
  out << "Система команд\n";
  out << "1. add <dict> <word> <translation1> <translation2> ... <translationN> - добавление слова в словарь.\n";
  out << "Добавить слово <word> с переводами <translation1>... в словарь <dict>. Если слово\n";
  out << "уже существует, то добавить переводы, которых ещё не было. Если добавлять нечего\n";
  out << "- такое слово уже существует и у него уже есть все указанные переводы, либо\n";
  out << "переводы не указаны, либо словаря <dict> не существует, то вывести сообщение <INVALID COMMAND>\n";
  out << "2. remove <dict> <word> [translation1] [translation2] ... [translationN] - удаление слов из словаря.\n";
  out << "Если указаны переводы, то убрать из словаря <dict> <word> все указанные переводы.\n";
  out << "Иначе убрать слово целиком. Если убирать нечего - ни одного из указанных переводов\n";
  out << "у слова нету, либо слова/словаря нет совсем, то вывести сообщение <INVALID COMMAND>\n";
  out << "3. save <dict> [file] - сохранение словаря <dict> в файл [file]\n";
  out << "Если файл не указан, то сохранить в файл с названием <dict>.\n";
  out << "Словарь сохраняется в следующем формате:\n";
  out << "<Слово на английском>:<слово на русском>,...<слово на русском>\n";
  out << "4. load <dict> [file] - загрузка словаря <dict> из файла <file>\n";
  out << "Загрузить словарь из файла [file]. Если файл не указан, то загрузить из файла с\n";
  out << "названием <dict>. Если файл не удовлетворят формату или не существует, то вывести <INVALID COMMAND>.\n";
  out << "5. list - вывод имён всех загруженных словарей.\n";
  out << "6. translate <word> [dict] - перевод слова на русский.\n";
  out << "Вывести все переводы слова <word> из словаря [dict]. Если [dict] не указан, то\n";
  out << "вывести переводы из всех словарей. Если слова <word> в словаре нет, или самого\n";
  out << "словаря нет, то вывести <INVALID COMMAND>.\n";
  out << "7. search <translation> [dict] - поиск слов с переводом.\n";
  out << "Вывести все слова из [dict], один из переводов которых совпадает с <translation>.\n";
  out << "Если [dict] не указан, то поиск производится по всем словарям. Если [dict] не\n";
  out << "существует, то вывести <INVALID COMMAND>.\n";
  out << "8. prefix <prefix> [dict] - поиск слов по префиксу.\n";
  out << "Вывести все слова в [dict], которые содержат префикс <prefix>. Если [dict] не\n";
  out << "указан, то поиск производится по всем словарям. Если [dict] не существует, то вывести <INVALID COMMAND>.\n";
  out << "9. merge <dict1> <dict2> <dict3> - объединить словарь с другим.\n";
  out << "В словарь <dict3> добавляются все слова и переводы из <dict1> и <dict2>.\n";
  out << "Если <dict1> или <dict2> не существуют, то вывести сообщение <INVALID COMMAND>\n";
  out << "10. exclude <dict1> <dict2> <dict3> - убрать из загруженного словаря переводы из другого.\n";
  out << "В <dict3> сохраняются все слова из <dict1>, кроме встречающихся в <dict2>.\n";
  out << "Если <dict1> или <dict2> не существуют, то вывести сообщение <INVALID COMMAND>\n";
  out << "11. split <dict1> <word> <dict2> <dict3> - разделить словарь на два.\n";
  out << "Сохранить все слова из <dict1> меньше <word> в <dict2>, а которые больше в <dict3>.\n";
  out << "Если <dict1>/<dict2>/<dict3> не существуют, или слова <word> в словаре <dict1> нету,\n";
  out << "то вывести <INVALID COMMAND>.\n";
}
