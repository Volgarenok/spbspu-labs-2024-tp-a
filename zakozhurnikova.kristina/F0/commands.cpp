#include "commands.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>

using namespace std::placeholders;

void addDictionary(std::string& dictionaryName, dictionaryOne& toAdd, dict& dictionary)
{
  if (toAdd.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  if (dictionary.find(dictionaryName) != dictionary.cend())
  {
    dictionary[dictionaryName] = std::move(toAdd);
  }
  else
  {
    dictionary[dictionaryName] = toAdd;
  }
}

void printWord(std::ostream& out, const std::string& translate)
{
  out << ' ' << translate;
}

void printPairTranslate(std::ostream& out, const std::pair< std::string, std::set< std::string > >& pair)
{
  out << ' ' << pair.first;
  std::for_each(pair.second.cbegin(), pair.second.cend(), std::bind(printWord, std::ref(out), _1));
}

void printDictionary(
  std::ostream& out, const std::pair< const std::string, std::map< std::string, std::set< std::string > > >& dict
)
{
  out << dict.first;
  std::for_each(dict.second.cbegin(), dict.second.cend(), std::bind(printPairTranslate, std::ref(out), _1));
  out << '\n';
}

void zakozhurnikova::print(const std::list< std::string >& args, std::ostream& out, const dict& dictionary)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }
  std::string mapName = args.back();
  if (!dictionary.at(mapName).empty())
  {
    const std::pair< const std::string, std::map< std::string, std::set< std::string > > >& oneDictionary =
      *dictionary.find(mapName);
    printDictionary(out, oneDictionary);
  }
  else
  {
    out << "<EMPTY>";
  }
}

bool identical(const dictionaryOne& second, std::pair< std::string, std::set< std::string > > word)
{
  return second.find(word.first) == second.cend();
}

void zakozhurnikova::complement(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;
  auto predicate = std::bind(identical, std::cref(secondMap), _1);
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

void zakozhurnikova::intersect(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;
  auto predicate = std::bind(std::logical_not< bool >{}, std::bind(identical, std::cref(secondMap), _1));
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

void zakozhurnikova::doUnion(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;

  copy(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()));
  auto predicate = std::bind(identical, std::cref(resultDict), _1);
  std::copy_if(secondMap.cbegin(), secondMap.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

bool checkSymbol(const std::string& temp)
{
  if (temp.size() != 1 || !((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z')))
  {
    return false;
  }
  return true;
}

bool isSymbol(const std::string& symbol, std::pair< std::string, std::set< std::string > > pair)
{
  std::string temp = pair.first;
  return temp[0] == symbol[0];
}

void zakozhurnikova::specificLetter(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.back());
  args.pop_back();
  std::string symbol = args.back();
  if (!checkSymbol(symbol))
  {
    throw std::invalid_argument("Incorrect symbol");
  }
  dictionaryOne resultDict;
  auto predicate = std::bind(isSymbol, symbol, _1);
  copy_if(current.cbegin(), current.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

void zakozhurnikova::elimination(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  args.pop_front();
  std::string translate = args.front();
  std::set< std::string >& temp = current[word];
  if (!temp.empty())
  {
    temp.clear();
  }
  temp.insert(translate);
  current[word] = temp;
}

void zakozhurnikova::destruction(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  try
  {
    dictionaryOne& current = dictionary.at(args.front());
    std::string word = args.back();
    current.erase(word);
  }
  catch (const std::out_of_range& e)
  {
    std::cout << "The word was not found\n";
  }
}

void zakozhurnikova::addition(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;
  auto predicateFirst = std::bind(identical, std::cref(secondMap), _1);
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()), predicateFirst);
  auto predicateSecond = std::bind(std::logical_not< bool >{}, std::bind(identical, std::cref(firstMap), _1));
  std::copy_if(secondMap.cbegin(), secondMap.cend(), std::inserter(resultDict, resultDict.end()), predicateSecond);

  firstMap.clear();
  firstMap = resultDict;
}

bool isPalindrome(std::pair< std::string, std::set< std::string > > pair)
{
  const std::string& word = pair.first;
  size_t len = word.length();
  for (size_t i = 0; i < len / 2; ++i)
  {
    if (word[i] != word[len - i - 1])
    {
      return false;
    }
  }
  return true;
}

void zakozhurnikova::palindrome(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.back());
  dictionaryOne resultDict;
  std::string nameDictionary = args.front();
  copy_if(current.cbegin(), current.cend(), std::inserter(resultDict, resultDict.end()), isPalindrome);
  if (!resultDict.empty())
  {
    addDictionary(nameDictionary, resultDict, dictionary);
  }
  else
  {
    std::cout << "<EMPTY>\n";
  }
}

void existTranslate(const std::string& translate, std::string temp)
{
  if (translate == temp)
  {
    throw std::logic_error("there is already a translation of word");
  }
}

void zakozhurnikova::rider(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  std::string translate = args.back();
  try
  {
    std::set< std::string >& temp = current.at(word);
    auto function = std::bind(existTranslate, translate, _1);
    std::for_each(temp.cbegin(), temp.cend(), function);
    temp.insert(translate);
  }
  catch (const std::out_of_range& e)
  {
    std::set< std::string > currentTranslate;
    currentTranslate.insert(translate);
    current[word] = currentTranslate;
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
  }
}

void outToString(std::string& result, const std::string& temp)
{
  result += ' ' + temp;
}

void zakozhurnikova::interpreter(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  std::string result;
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  if (current.find(word) != current.cend())
  {
    result += *current[word].cbegin();
    auto function = std::bind(outToString, std::ref(result), _1);
    std::for_each(++current[word].cbegin(), current[word].cend(), function);
  }
  else
  {
    result = "<EMPTY>";
  }
  std::cout << result << '\n';
}

void zakozhurnikova::save(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }
  std::string fileName = args.back();
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("Couldn't open file");
  }
  std::for_each(dictionary.cbegin(), dictionary.cend(), std::bind(printDictionary, std::ref(file), _1));
  file.close();
}

void zakozhurnikova::doAddDictionary(std::list< std::string >&, std::istream& in, dict& dictionary)
{
  ScopeGuard guard(in);
  std::string nameDictionary;
  in >> nameDictionary;
  subDict translation;
  in >> std::noskipws;
  in >> translation;
  if (!translation.empty() && !nameDictionary.empty() && isDictionary(nameDictionary, dictionary))
  {
    dictionary[nameDictionary] = translation;
  }
  else if (!nameDictionary.empty())
  {
    std::cout << "The dictionary is empty:" << nameDictionary << '\n';
  }
}
