#include "commands.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>
#include "dictionary.hpp"

namespace demidenko
{
  const char* ERROR_MESSAGE = "Error accured\n";
  std::istream& readMainAndOptional(std::istream& in, std::string& main, std::string& optional)
  {
    in >> main;
    if (in.fail())
    {
      return in;
    }
    if (in.peek() != '\n')
    {
      in >> optional;
    }
    return in;
  }
}
void demidenko::doCheckCmd(std::ostream& out, const char* fileName)
{
  std::ifstream inFile(fileName);
  Dictionary::Record record;
  while (!inFile.eof())
  {
    readRecord(inFile, record);
    if (!inFile.eof() && inFile.fail())
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
  in >> dictionaryName;
  readRecord(in, record);
  if (in.fail() || !dictionaries.at(dictionaryName).addRecord(std::move(record)))
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::doRemoveCmd(std::istream& in, std::map< std::string, Dictionary >& dictionaries)
{
  std::string dictionaryName;
  Dictionary::Record record;
  in >> dictionaryName;
  readRecord(in, record);
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
  if (readMainAndOptional(in, dictionaryName, fileName).fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
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
  if (readMainAndOptional(in, dictionaryName, fileName).fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  std::ifstream inFile;
  if (fileName.empty())
  {
    inFile.open(dictionaryName);
  }
  else
  {
    inFile.open(fileName);
  }
  Dictionary dictionary;
  inFile >> dictionary;
  if (inFile.fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  dictionaries[dictionaryName] = dictionary;
}
void demidenko::doListCmd(std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  using OutputIterator = std::ostream_iterator< std::string >;
  const std::string& (*getFirst)(const std::pair< std::string, Dictionary >&) = std::get< 0 >;
  std::transform(dictionaries.begin(), dictionaries.end(), OutputIterator{ out, "\n" }, getFirst);
}
namespace demidenko
{
  struct TranslatePair
  {
    std::ostream& out;
    const std::string& word;
    bool operator()(const std::pair< std::string, Dictionary >& dictionary)
    {
      return dictionary.second.translate(word, out);
    }
  };
}
void demidenko::doTranslateCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  std::string word;
  std::string dictionaryName;
  if (readMainAndOptional(in, word, dictionaryName).fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  if (dictionaryName.empty())
  {
    bool isSuccessful = std::count_if(dictionaries.begin(), dictionaries.end(), TranslatePair{ out, word });
    if (!isSuccessful)
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
  }
  else
  {
    dictionaries.at(dictionaryName).translate(word, out);
  }
}
void demidenko::doSearchCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  std::string translation;
  std::string dictionaryName;
  if (readMainAndOptional(in, translation, dictionaryName).fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  if (dictionaryName.empty())
  {
    for (auto& dictionary : dictionaries)
    {
      dictionary.second.search(translation, out);
    }
  }
  else
  {
    dictionaries.at(dictionaryName).search(translation, out);
  }
}
void demidenko::doPrefixCmd(std::istream& in, std::ostream& out, std::map< std::string, Dictionary >& dictionaries)
{
  std::string prefix;
  std::string dictionaryName;
  if (readMainAndOptional(in, prefix, dictionaryName).fail())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  if (dictionaryName.empty())
  {
    for (auto& dictionary : dictionaries)
    {
      dictionary.second.prefix(prefix, out);
    }
  }
  else
  {
    dictionaries.at(dictionaryName).prefix(prefix, out);
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
  out << "Command line parameters:\n";
  out << "<dict> [file] startup loading a dictionary named <dict> from file [file], if\n";
  out << "specified. Otherwise load from file <dict>\n";
  out << "--help show help info\n";
  out << "--check <file> check if the dictionary in the <file> is correct\n\n";
  out << "Command system:\n";
  out << "add <dict> <word>:<translation1>,<translation2>,...<translationN> - add word to dictionary.\n";
  out << "remove <dict> <word>:[translation1],[translation2],...[translationN] - remove word from dictionary.\n";
  out << "save <dict> [file] - save dictionary to file\n";
  out << "load <dict> [file] - load dictionary from file\n";
  out << "list - print all loaded dictionaries;\n";
  out << "translate <word> [dict] - translate to russian\n";
  out << "search <translation> [dict] - search word by its translation\n";
  out << "prefix <prefix> [dict] - search word by its prefix\n";
  out << "merge <dict1> <dict2> <dict3> - merge two dictionaries into third\n";
  out << "exclude <dict1> <dict2> <dict3> - add all words from first that do not appear in second to third\n";
  out << "split <dict1> <word> <dict2> <dict3> - split the dictionary into two parts\n";
}
