#include "Utilites.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>

namespace erfurt
{
  std::string oneWord(std::string & str)
  {
    std::string word = str.substr(0, str.find_first_of(' '));
    if (str.find_first_of(' ') == std::string::npos)
    {
      word = str;
      str.clear();
    }
    else
    {
      str.erase(0, str.find_first_of(' ') + 1);
    }
    return word;
  }

  bool isEng(const std::string & word)
  {
    return count_if(word.begin(), word.end(),
      [](const char& el) { return (el >= 'A' && el <= 'z') || el == ' '; }) == word.size();
  }

  bool isRus(const std::string & translate)
  {
    return count_if(translate.begin(), translate.end(),
      [](const char& el) { return (el >= 'À' && el <= 'ÿ') || el == ' '; }) == translate.size();
  }

  std::vector<Dictionary> createDictionaryFromFile(std::istream & fin)
  {
    std::vector<Dictionary> resultVector;
    while (!fin.eof())
    {
      Dictionary dictionary;
      fin >> dictionary;
      if (!dictionary.getName().empty())
      {
        resultVector.push_back(dictionary);
      }
    }
    return resultVector;
  }

  Dictionary createCommonDictionary(const Dictionary & dict1, const Dictionary & dict2)
  {
    Dictionary result(dict1.getName() + dict2.getName());

    auto pair1 = dict1.begin();
    auto pair2 = dict2.begin();
    while (pair1 != dict1.end() && pair2 != dict2.end())
    {
      if (pair1->first > pair2->first)
      {
        pair2++;
      }
      else if (pair1->first < pair2->first)
      {
        pair1++;
      }
      else
      {
        auto translate1 = *pair1->second;
        auto translate2 = *pair2->second;
        for (const auto& tr : translate1)
        {
          if (translate2.find(tr) != translate2.cend())
          {
            result.insert(pair1->first, tr);
          }
        }
        pair1++;
        pair2++;
      }
    }
    return result;
  }

  Dictionary createUniqueDictionary(const Dictionary & dict1, const Dictionary & dict2)
  {
    Dictionary result(dict1.getName() + "\\" + dict2.getName());

    auto pair1 = dict1.begin();
    auto pair2 = dict2.begin();
    while (pair1 != dict1.end() && pair2 != dict2.end())
    {
      if (pair1->first < pair2->first)
      {
        result.insert({ pair1->first, pair1->second });
        pair1++;
      }
      else if (pair1->first > pair2->first)
      {
        result.insert({ pair2->first, pair2->second });
        pair2++;
      }
      else
      {
        pair1++;
        pair2++;
      }
    }
    while (pair2 != dict2.end())
    {
      result.insert({ pair2->first, pair2->second });
      pair2++;
    }
    while (pair1 != dict1.end())
    {
      result.insert({ pair1->first, pair1->second });
      pair1++;
    }
    return result;
  }
}
