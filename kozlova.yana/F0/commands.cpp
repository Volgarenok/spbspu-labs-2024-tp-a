#include "commands.hpp"
#include <vector>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <exception>
#include <string>
#include <map>
#include <vector>
#include <numeric>
#include "dictionary.hpp"

namespace kozlova
{
  void printHelp(std::ostream& out)
  {
    out << "Command system:\n";
    out << "1. read <dictionary> <file> - create a new dictionary based on the input file.\n";
    out << "2. readPart <dictionary> <file> <from> <before> - create a new dictionary and add words from the input file from a specific word to a specific word to it.\n";
    out << "3. maxFreq <dictionary> - find the most frequently used word in the dictionary.\n";
    out << "4. combine <dict to combine> <dict1> <dict2> - creates a dictionary that includes all objects from the other two dictionaries, without repetition.\n";
    out << "5. remove <dict1> <dict2> -  delete words from an existing dictionary that are stored in another existing dictionary.\n";
    out << "6. delete <dictionary> - deleting a dictionary.\n";
    out << "7. printFreq <dictionary> <key> - output the frequency of the key word.\n";
    out << "8. predecessor <dictionary> <number> - print the number of words that are contained in the dictionary, used more often than a certain number of times.\n";
    out << "9. delPhrase <dictionary> <phrase> - deleting all words from the dictionary that contain a certain substring.\n";
    out << "10. sumFreq <dictionary> <phrase> - find the total frequency of words starting with a certain prefix.\n";
    out << "11. print <dictionary> - displays the dictionary in alphabetical order.\n";
  }

  struct isName
  {
    bool operator()(const std::pair<std::string, Dictionary>& pair, const std::string& name)
    {
      return pair.first == name;
    }
  };

  void read(std::map< std::string, Dictionary >& dictionaries, std::istream& in)
  {
    std::string name;
    std::string file;
    in >> name >> file;
    std::ifstream input(file);
    auto pred = std::bind(isName(), std::placeholders::_1, name);
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), pred);
    if (iterator != dictionaries.end() || !in || !input)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary dict_new;
    dict_new.insertWords(input);
    dictionaries.insert(std::pair< std::string, Dictionary >(name, dict_new));
  }

  void readPart(std::map< std::string, Dictionary >& dictionaries, std::istream& in)
  {
    std::string name;
    std::string file;
    std::string from;
    std::string before;
    in >> name >> file >> from >> before;
    std::ifstream input(file);
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, name));
    if (iterator != dictionaries.end() || !in || !input)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary dict_new;
    dict_new.insertPart(input, from, before);
    dictionaries.insert(std::pair< std::string, Dictionary >(name, dict_new));
  }

  bool isMaxFreq(const pair& first, const pair& second)
  {
    return ( first.second < second.second);
  }

  void findMaxFreq(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    in >> dictName;
    auto pred = std::bind(isName(), std::placeholders::_1, dictName);
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), pred);
    if (iterator == dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary dict = dictionaries[dictName].getDict();
    if (dict.empty())
    {
      throw std::logic_error("<EMPTY DICTIONARY>");
    }

    auto maxFreq = std::max_element(dict.cbegin(), dict.cend(), isMaxFreq);
    if (maxFreq != dict.cend())
    {
      out << maxFreq->first << std::endl;
    }
  }

  void addInDict(const pair& pair, Dictionary& dict)
  {
    dict.addWord(pair.first, pair.second);
  }

  Dictionary createCombo(const std::map< std::string, size_t >& dict1, const std::map< std::string, size_t >& dict2)
  {
    Dictionary combo(dict1);
    auto pred = std::bind(addInDict, std::placeholders::_1, std::ref(combo));
    std::for_each(dict2.cbegin(), dict2.cend(), pred);
    return combo;
  }

  void combiningDictionary(std::map< std::string, Dictionary >& dictionaries, std::istream& in)
  {
    std::string dictNew;
    std::string name1;
    std::string name2;
    in >> dictNew >> name1 >> name2;
    auto iteratorNew = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, dictNew));
    auto iterator1 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, name1));
    auto iterator2 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, name2));
    if (iteratorNew != dictionaries.end() || iterator1 == dictionaries.end() || iterator2 == dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    std::map< std::string, size_t > dict1 = dictionaries[name1].getDict();
    std::map< std::string, size_t > dict2 = dictionaries[name2].getDict();
    Dictionary dictCombo = createCombo(dict1, dict2);
    dictionaries.insert(std::pair< std::string, Dictionary >(dictNew, dictCombo));
  }

  void deleteInDict(const pair& pair, Dictionary& dict)
  {
    dict.deleteWord(pair.first);
  }

  void removeWords(std::map< std::string, Dictionary >& dictionaries, std::istream& in)
  {
    std::string name1;
    std::string name2;
    in >> name1 >> name2;
    auto iterator1 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, name1));
    auto iterator2 = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, name2));
    if (iterator1 == dictionaries.end() || iterator2 == dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary& dict1 = iterator1->second;
    const Dictionary& dict2 = iterator2->second;
    std::for_each(dict2.cbegin(), dict2.cend(), std::bind(&deleteInDict, std::placeholders::_1, std::ref(dict1)));
  }

  void deleteDictionary(std::map< std::string, Dictionary >& dicts, std::istream& in)
  {
    std::string dictName;
    in >> dictName;
    dicts.erase(dictName);
  }

  bool isOften(const pair& node, const size_t& number)
  {
    return node.second > number;
  }

  void predecessor(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    std::string arg;
    in >> dictName >> arg;
    size_t num = std::stoull(arg);
    auto pred = std::bind(isName(), std::placeholders::_1, dictName);
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), pred);
    if (iterator == dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary dict = dictionaries[dictName].getDict();
    if (dict.empty())
    {
      throw std::logic_error("<EMPTY DICTIONARY>");
    }

    int count = std::count_if(dict.cbegin(), dict.cend(), std::bind(isOften, std::placeholders::_1, num));
    out << count << '\n';
  }

  void printFreqWord(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string nameDict;
    std::string word;
    in >> nameDict;
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, nameDict));
    if (iterator != dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary dict = dictionaries[nameDict].getDict();
    in >> word;
    auto iterW = dict.search(word);
    if (iterW != dict.end())
    {
      out << dict.getOften(word) << '\n';
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }

  void printElement(const pair& item, std::ostream& out)
  {
    out << item.first << ' ' << item.second << '\n';
  }

  void printDictCmd(const std::map< std::string, Dictionary >& dicts, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    in >> dictName;
    const Dictionary& dict = dicts.at(dictName);
    using namespace std::placeholders;
    auto outFunc = std::bind(printElement, _1, std::ref(out));
    std::for_each(dict.cbegin(), dict.cend(), outFunc);
  }

  bool isPhrase(const pair& pair, const std::string& phrase)
  {
    if (pair.first.find(phrase) != std::string::npos)
    {
      return true;
    }
    return false;
  }

  void deleteWithPhrase(std::map< std::string, Dictionary >& dictionaries, std::istream& in)
  {
    std::string dictName;
    std::string phrase;
    in >> dictName >> phrase;
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, dictName));
    if (iterator == dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary& dict = iterator->second;
    std::vector< pair > wordsToDelete;
    wordsToDelete.reserve(dict.size());
    std::copy_if(dict.cbegin(), dict.cend(), std::back_inserter(wordsToDelete), std::bind(isPhrase, std::placeholders::_1, phrase));
    for_each(wordsToDelete.cbegin(), wordsToDelete.cend(), std::bind(&deleteInDict, std::placeholders::_1, std::ref(dict)));
  }

  size_t getSum(size_t sum, const std::pair<std::string, size_t>& pair2)
  {
    return sum + pair2.second;
  }

  void findFrequencyPhrase(std::map< std::string, Dictionary >& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dictName;
    std::string phrase;
    in >> dictName >> phrase;
    auto iterator = std::find_if(dictionaries.begin(), dictionaries.end(), std::bind(isName(), std::placeholders::_1, dictName));
    if (iterator == dictionaries.end() || !in)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Dictionary& dict = iterator->second;
    std::vector< pair > select;
    select.reserve(dict.size());
    std::copy_if(dict.cbegin(), dict.cend(), std::back_inserter(select), std::bind(isPhrase, std::placeholders::_1, phrase));
    auto sum = std::accumulate(select.cbegin(), select.cend(), size_t(0), getSum);
    out << sum << '\n';
  }
}
