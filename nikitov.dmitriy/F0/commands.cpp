#include "commands.hpp"
#include <fstream>
#include <functional>
#include <algorithm>
#include <utility>
#include <iterator>
#include <vector>
#include <locale>
#include "dictionary.hpp"

void nikitov::printHelp(std::ostream& output)
{
  output << "Command system:" << '\n'
    << "1. print dictionary <dictName> - output of all words in the specified dictionary" << '\n'
    << "2. print all - output of all words from all dictionaries" << '\n'
    << "3. print names - output the names of all dictionaries" << '\n'
    << "4. find translation <dictName> <word> - search and output of a word translation from the dictionary" << '\n'
    << "5. find antonym <dictName> <word> - search and output of the word's antonyms from the dictionary" << '\n'
    << "6. translate sentence <dictName> - outputs a machine translation of a sentence based on the specified dictionary" << '\n'
    << "7. translate file <dictName> <inputFile> <outputFile> - reads text from a file and writes the translation to another file" << '\n'
    << "8. save dictionary <dictName> <newFileName> - saves the specified dictionary to a file" << '\n'
    << "9. create dictionary <dictName> - creates an empty dictionary with the specified name" << '\n'
    << "10. add translation <dictName> <word> <translation> - adds a word with a translation to the specified dictionary" << '\n'
    << "11. add antonym <dictName> <word> <antonym> - adds an antonym to the word" << '\n'
    << "12. edit primary <dictName> <word> - changes the main translation of the word" << '\n'
    << "13. edit secondary <dictName> <word> - changes the second translation of the word" << '\n'
    << "14. delete primary <dictName> <word> - delete the main translation of the word" << '\n'
    << "15. delete secondary <dictName> <word> - delete the second translation of the word" << '\n'
    << "16. delete antonym <dictName> <word> - remove the antonym of the word" << '\n'
    << "17. merge dictionary <firstDictName> <secondDictName> <newDictName> - creates a new dictionary based on the other two" << '\n';
}

void nikitov::printDictCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;
  output << dictOfDicts.at(dictName);
}

void nikitov::printAllCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  std::vector< Dictionary > dicts;
  auto get = static_cast< const Dictionary& (*)(const std::pair< std::string, Dictionary >&) >(std::get< 1 >);
  std::transform(dictOfDicts.cbegin(), dictOfDicts.cend(), std::back_inserter(dicts), get);
  std::copy(dicts.cbegin(), dicts.cend(), std::ostream_iterator< Dictionary >(output));
}

void nikitov::printNamesCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  std::vector< std::string > names;
  auto get = static_cast< const std::string& (*)(const std::pair< std::string, Dictionary >&) >(std::get< 0 >);
  std::transform(dictOfDicts.cbegin(), dictOfDicts.cend(), std::back_inserter(names), get);
  auto plus = std::bind(std::plus< std::string >(), std::placeholders::_1, "\n");
  std::transform(names.cbegin(), names.cend(), names.begin(), plus);
  std::copy(names.cbegin(), names.cend(), std::ostream_iterator< std::string >(output));
}

void nikitov::findCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output,
  const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "translation")
  {
    output << dictOfDicts.at(dictionaryName).findWord(word) << '\n';
  }
  else
  {
    output << dictOfDicts.at(dictionaryName).findAntonym(word) << '\n';
  }
}

char translate(const std::map< std::string, nikitov::Dictionary >& dictOfDicts, const std::string& dictionaryName,
  std::istream& input, std::ostream& output)
{
  std::string line;
  std::locale loc;
  input >> line;
  std::string temp = line;
  std::transform(temp.begin(), temp.end(), temp.begin(), std::bind(std::tolower< char >, std::placeholders::_1, loc));

  char symb = ' ';
  try
  {
    if (!temp.empty() && !std::isalpha(temp.back()))
    {
      symb = temp.back();
      temp.pop_back();
      line.pop_back();
    }
    temp = dictOfDicts.at(dictionaryName).findTranslation(temp);
    output << temp;
  }
  catch (const std::exception&)
  {
    output << line;
  }
  if (symb != ' ')
  {
    output << symb;
  }
  return symb;
}

void nikitov::translateSentenceCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictionaryName;
  input >> dictionaryName;
  char symb = ' ';
  bool isFirst = true;

  while (input && symb != '.')
  {
    if (!isFirst)
    {
      output << ' ';
    }
    isFirst = false;
    symb = translate(dictOfDicts, dictionaryName, input, output);
  }
  output << '\n';
}

void nikitov::translateFileCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string fileName;
  input >> fileName;
  std::string newFileName;
  input >> newFileName;

  std::ifstream fileInput(fileName);
  std::ofstream fileOutput(newFileName);
  bool isFirst = true;

  while (fileInput)
  {
    if (!isFirst)
    {
      fileOutput << ' ';
    }
    isFirst = false;
    translate(dictOfDicts, dictionaryName, fileInput, fileOutput);
  }
  fileOutput << '\n';
}

void nikitov::saveCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string dictName;
  input >> dictName;
  std::string newFileName;
  input >> newFileName;
  std::ofstream fileOutput(newFileName);
  fileOutput << dictOfDicts.at(dictName);
}

void nikitov::createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  if (!dictOfDicts.insert({ dictionaryName, Dictionary() }).second)
  {
    throw std::logic_error("<ERROR: ALREADY EXIST>");
  }
}

void nikitov::addCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  std::string translation;
  input >> word >> translation;
  if (parameter == "translation")
  {
    dictOfDicts.at(dictionaryName).addTranslation(word, translation);
  }
  else
  {
    dictOfDicts.at(dictionaryName).addAntonym(word, translation);
  }
}

void nikitov::editCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  std::string translation;
  input >> translation;
  if (parameter == "primary")
  {
    dictOfDicts.at(dictionaryName).editPrimaryTranslation(word, translation);
  }
  else
  {
    dictOfDicts.at(dictionaryName).editSecondaryTranslation(word, translation);
  }
}

void nikitov::deleteCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "primary")
  {
    dictOfDicts.at(dictionaryName).deletePrimaryTranslation(word);
  }
  else if (parameter == "secondary")
  {
    dictOfDicts.at(dictionaryName).deleteSecondaryTranslation(word);
  }
  else
  {
    dictOfDicts.at(dictionaryName).deleteAntonym(word);
  }
}

void nikitov::mergeCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string firstDictionaryName;
  input >> firstDictionaryName;
  auto firstDict = dictOfDicts.at(firstDictionaryName);
  std::string secondDictionaryName;
  input >> secondDictionaryName;
  auto secondDict = dictOfDicts.at(secondDictionaryName);
  std::string newDictionaryName;
  input >> newDictionaryName;
  auto newDict = firstDict;
  std::copy(secondDict.data_.cbegin(), secondDict.data_.cend(), std::inserter(newDict.data_, newDict.data_.end()));
  dictOfDicts.insert({ newDictionaryName, newDict });
}
