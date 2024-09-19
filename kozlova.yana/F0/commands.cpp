#include "commands.hpp"
#include <vector>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <exception>
#include "dictionary.hpp"

namespace kozlova
{
  struct isName
  {
    bool operator()(const std::pair<std::string, Dictionary>& pair, const std::string& name)
    {
      return pair.second.getName() == name;
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
    auto iterator = dict.search(pair.first);
    if (iterator != dict.end())
    {
      return;
    }
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

  void mergeDict(Dictionary& dict1, const Dictionary& dict2)
  {
    auto pred = std::bind(deleteInDict, std::placeholders::_1, std::ref(dict1));
    std::for_each(dict2.cbegin(), dict2.cend(), pred);
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
    Dictionary dict1 = dictionaries[name1].getDict();
    Dictionary dict2 = dictionaries[name2].getDict();

    mergeDict(dict1, dict2);
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
}
