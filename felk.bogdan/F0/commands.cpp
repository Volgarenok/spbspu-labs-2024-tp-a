#include "commands.hpp"

#include <functional>
#include <algorithm>
#include <cstring>
#include <set>
#include <fstream>
#include <cmath>

namespace felk
{
  bool ifMoreFreq(const std::pair< std::string, size_t > elem, size_t num, Dict& dict)
  {
    if (elem.second > num)
    {
      dict.erase(elem.first);
      return true;
    }
    return false;
  }

  std::pair< std::string, size_t > getMeanElem(const std::string& key, Dict& dict1, Dict& dict2)
  {
    double res = 0.0;
    if (dict1.count(key) == 1 && dict2.count(key) == 1)
    {
      res = (dict1[key] + dict2[key]) / 2;
    }
    else if (dict1.count(key) == 1)
    {
      res = dict1[key] / 2;
    }
    else
    {
      res = dict2[key] / 2;
    }
    return std::make_pair(key, std::ceil(res));
  }

  std::string getKey(const std::pair< std::string, size_t >& data)
  {
    return data.first;
  }

  bool ifContainsStr(const std::pair< std::string, size_t >& data, const std::string& sub)
  {
    return data.first.find(sub) != std::string::npos;
  }

  void printPair(const std::pair< std::string, size_t >& data, std::ostream& out)
  {
    out << data.second << " " << data.first << "\n";
  }

  bool ifUnique(const std::pair< std::string, size_t >& data, const Dict& dict2)
  {
    return dict2.count(data.first) == 0;
  }

  bool ifNotLess(const std::pair< std::string, size_t >& data, size_t num)
  {
    return data.first.length() >= num;
  }
}

void felk::split(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name1 = "";
  std::string name2 = "";
  size_t n = 0;
  in >> name1 >> name2 >> n;
  Dict newDict;
  Dict& dict1 = dicts.at(name1);
  auto filter = std::bind(ifMoreFreq, std::placeholders::_1, n, dict1);
  std::copy_if(dict1.begin(), dict1.end(), std::inserter(newDict, newDict.begin()), filter);
  if (newDict.empty())
  {
    throw std::invalid_argument("NO MATCHES");
  }
  dicts.insert(std::make_pair(name2, newDict));
}

void felk::setNewNumber(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  std::string key = "";
  size_t n = 0;
  in >> name >> key >> n;
  if (dicts.count(name) == 0)
  {
    throw std::invalid_argument("WRONG DICT");
  }
  Dict& dict = dicts.at(name);
  try
  {
    dict.at(key) = n;
  }
  catch (...)
  {
    throw std::invalid_argument("NO MATCHES");
  }
}

void felk::getMean(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name1 = "";
  std::string name2 = "";
  std::string nameNew = "";
  in >> nameNew >> name1 >> name2;
  Dict newDict;
  if (dicts.count(name1) == 0 || dicts.count(name2) == 0)
  {
    throw std::invalid_argument("WRONG DICT");
  }
  const Dict& dict1 = dicts.at(name1);
  const Dict& dict2 = dicts.at(name2);
  std::set< std::string > keys;
  std::transform(dict1.cbegin(), dict1.cend(), std::inserter(keys, keys.begin()), getKey);
  std::transform(dict2.cbegin(), dict2.cend(), std::inserter(keys, keys.begin()), getKey);
  auto func = std::bind(getMeanElem, std::placeholders::_1, dict1, dict2);
  std::transform(keys.cbegin(), keys.cend(), std::inserter(newDict, newDict.begin()), func);
  dicts.insert(std::make_pair(nameNew, newDict));
}

void felk::deleteKey(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  std::string key = "";
  in >> name >> key;
  Dict& dict = dicts[name];
  if (dict.count(key) == 0)
  {
    throw std::invalid_argument("NO MATCHES");
  }
  dict.erase(key);
}

void felk::clear(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  in >> name;
  Dict& dict = dicts[name];
  if (dict.empty())
  {
    throw std::invalid_argument("ALREADY EMPTY");
  }
  dict.clear();
}

void felk::filter(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  std::string str = "";
  if (dicts.count(name) == 0)
  {
    throw std::invalid_argument("WRONG DICT");
  }
  Dict& dict = dicts[name];
  if (dict.empty())
  {
    throw std::invalid_argument("WRONG DICT");
  }
  auto func = std::bind(ifContainsStr, std::placeholders::_1, std::cref(str));
  Dict temp;
  std::copy_if(dict.cbegin(), dict.cend(), std::inserter(temp, temp.begin()), func);
  dict = temp;
}

void felk::print(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.count(name) == 0 || dicts[name].empty())
  {
    throw std::invalid_argument("WRONG DICT");
  }
  Dict& dict = dicts[name];
  auto func = std::bind(printPair, std::placeholders::_1, std::ref(out));
  std::for_each(dict.cbegin(), dict.cend(), func);
}

void felk::getUnique(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name1 = "";
  std::string name2 = "";
  std::string newName = "";
  in >> newName >> name1 >> name2;
  if (dicts.count(newName) == 1)
  {
    throw std::invalid_argument("ALREADY EXISTS");
  }
  if (dicts.count(name1) == 0 || dicts.count(name2) == 0)
  {
    throw std::invalid_argument("WRONG DICT");
  }
  const Dict& dict1 = dicts[name1];
  const Dict& dict2 = dicts[name2];
  auto checkFst = std::bind(ifUnique, std::placeholders::_1, dict2);
  Dict temp;
  std::copy_if(dict1.cbegin(), dict1.cend(), std::inserter(temp, temp.begin()), checkFst);
  auto checkScd = std::bind(ifUnique, std::placeholders::_1, dict1);
  std::copy_if(dict2.cbegin(), dict2.cend(), std::inserter(temp, temp.begin()), checkScd);
  dicts.insert(std::make_pair(newName, temp));
}

void felk::lenFilter(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  size_t n = 0;
  in >> name >> n;
  if (dicts.count(name) == 0 || dicts[name].empty())
  {
    throw std::invalid_argument("WRONG DICT");
  }
  Dict& dict = dicts[name];
  Dict temp;
  auto filter = std::bind(ifNotLess, std::placeholders::_1, n);
  std::copy_if(dict.cbegin(), dict.cend(), std::inserter(temp, temp.begin()), filter);
  dict = temp;
}

void felk::makeDict(std::istream& in, std::ostream& out, std::unordered_map< std::string, Dict >& dicts)
{
  std::string name = "";
  std::string file = "";
  in >> name >> file;
  if (dicts.count(name) == 1)
  {
    throw std::invalid_argument("DICT EXISTS");
  }
  std::ifstream fin(file);
  if (fin.peek() == EOF)
  {
    throw std::invalid_argument("EMPTY FILE");
  }
  Dict newDict;
  std::string word;
  while (fin >> word)
  {
    newDict[word]++;
  }
  dicts.insert(std::make_pair(name, newDict));
}
