#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include <random>
#include <windows.h>
#include <list>
#include <set>

using val_t = std::pair< std::string, std::list< std::string > >;
using mainDict = std::map< std::string, val_t >;

mainDict unique(mainDict& dict1, mainDict& dict2)
{
  mainDict res;
  std::set< std::string > uniqueKeys;
  for (const auto& key: dict1)
  {
    uniqueKeys.insert(key.first);
  }
  for (const auto& key: dict2)
  {
    uniqueKeys.insert(key.first);
  }
  for (const auto& key : uniqueKeys)
  {
    if (dict1.count(key) > 0)
    {
      res[key] = dict1.at(key);
    }
    else if (dict2.count(key) > 0)
    {
      res[key] = dict2.at(key);
    }
  }
  return res;
}

mainDict search(mainDict& res, mainDict& dict1, mainDict& dict2, std::istream& in)
{
  std::string line1 = {};
  std::string line2 = {};
  in >> line1 >> line2;
  // check empty dicts
  if (line1 == "" || line2 == "")
  {
    throw std::logic_error("The range can't be empty");
  }
  auto begin1 = dict1.find(line1);
  while (begin1 != dict1.end()  && begin1->first != line2)
  {
    res.insert(*begin1);
    begin1++;
  }
  auto begin2 = dict2.find(line1);
  while (begin2 != dict2.cend() && begin2->first != line2)
  {
    res.insert(*begin2);
    begin2++;
  }
  return res;
}

template< class T >
T randomNumber(T min, T max)
{
  std::random_device random;
  std::mt19937 num(random());
  std::uniform_real_distribution< float > dist(min, max);
  return static_cast< T >(dist(num));
}

void random(mainDict& res, size_t count, mainDict& dict1, mainDict& dict2)
{
  if (dict1.size() + dict2.size() < count)
  {
    throw std::logic_error("Not enough keys");
  }
  if (count == 0)
  {
    throw std::logic_error("Count can't be zero");
  }
  if (count % 2 == 1)
  {
    for (size_t i = 0; i < (count / 2); i++)
    {
      size_t dist = randomNumber(0ull, dict1.size());
      auto it1 = dict1.begin();
      std::advance(it1, dist);
      res.insert(*it1);
    }
    for (size_t i = 0; i < (count / 2) + 1; i++)
    {
      size_t dist = randomNumber(0ull, dict2.size());
      auto it2 = dict2.begin();
      std::advance(it2, dist);
      res.insert(*it2);
    }
  }
  else
  {
    for (size_t i = 0; i < count / 2; i++)
    {
      size_t dist = randomNumber(0ull, dict1.size());
      auto it1 = dict1.begin();
      std::advance(it1, dist);
      res.insert(*it1);
    }
    for (size_t i = 0; i < count / 2; i++)
    {
      size_t dist = randomNumber(0ull, dict2.size());
      auto it2 = dict2.begin();
      std::advance(it2, dist);
      res.insert(*it2);
    }
  }
}

void save(const mainDict& dict, const std::string& name)
{
  if (dict.empty())
  {
    throw std::logic_error("Nothing to save");
  }
  std::fstream file(name);
  auto begin = dict.cbegin();
  SetConsoleCP(1251);
  while (begin != dict.cend())
  {
    file << begin->first << ' ' << begin->second.first << begin->second.second.front() << '\n';
    begin++;
  }
  SetConsoleCP(866);
}

void editTranslation(mainDict& dict, std::istream& in)
{
  std::string word = {};
  std::string trans = {};
  std::cout << "Please, input the word and a new translation\n";
  in >> word >> trans;
  auto it = dict.find(word);
  it->second.first = trans;
}

void editExample(mainDict& dict, std::istream& in)
{
  std::string example = {};

}


mainDict merge(mainDict& dict1, mainDict& dict2)
{
  if (dict1.empty() && !(dict2.empty()))
  {
    return dict2;
  }
  else if (dict2.empty() && !dict1.empty())
  {
    return dict1;
  }
  else if (!dict1.empty() && !dict2.empty())
  {
    mainDict res;
    auto begin1 = dict1.cbegin();
    while (begin1 != dict1.cend())
    {
      res.insert(*begin1);
      begin1++;
    }
    auto begin2 = dict2.cbegin();
    while (begin2 != dict2.cend())
    {
      res.insert(*begin2);
      begin2++;
    }
    return res;
  }
  else
  {
    throw std::logic_error("Both dicts are empty");
  }
}

void printHelp()
{
  std::cout << "Commands: \n";
  std::cout << "1) find - < word >\n";
  std::cout << "2) insert - < word > < translation > < example >\n";
  std::cout << "3) delete - < word >\n";
  std::cout << "4) merge - < dict name > < dict name >\n";
  std::cout << "5) save - < dict name > < output >\n";
  std::cout << "6) unique - < dict name > < dict name >\n";
  std::cout << "7) print - < dict name >\n";
  std::cout << "8) random - < count > < dict name > < dict name >\n";
  std::cout << "9) search - < dict name > < word > < word >\n";
  std::cout << "10) edit - < word > < new translation >\n";
}

void deleteWord(mainDict& dict, std::string& key)
{
  auto val = dict.find(key);
  if (val == dict.cend())
  {
    throw std::logic_error("Dict can't delete the word, because this word doesn't exist");
  }
  dict.erase(key);
}

void find(const mainDict& dict, std::string& key, std::ostream& out)
{
  if (dict.empty())
  {
    throw std::logic_error("Empty dict");
  }
  auto val = dict.find(key);
  if (val == dict.cend())
  {
    throw std::out_of_range("Dict doesn't have this key");
  }
  out << val->second.first << val->second.second.front();
}

void insert(mainDict& dict, std::istream& in)
{
  while (!in.eof())
  {
    in.clear();
    std::string word = {};
    in >> word;
    std::string translation = {};
    while (in >> translation)
    {
      std::string example = {};
      std::getline(in, example);
      val_t pair;
      pair.first = translation;
      pair.second.push_back(example);
      dict[word] = pair;
      in >> word;
    }
  }
  in.clear();
}

void inputDict(std::istream& in, mainDict& dict)
{
  while (!in.eof())
  {
    in.clear();
    std::string word = {};
    in >> word;
    std::string translation = {};
    while (in >> translation)
    {
      std::string example = {};
      std::getline(in, example);
      val_t pair;
      pair.first = translation;
      pair.second.push_back(example);
      dict[word] = pair;
      in >> word;  
    }
  }
  in.clear();
}

void print(const mainDict& dict, std::ostream& out)
{
  if (dict.empty())
  {
    throw std::logic_error("Empty dict");
  }
  auto begin = dict.cbegin();
  while (begin != dict.cend())
  {
    out << begin->first << ' ' << begin->second.first << begin->second.second.front() << '\n';
    begin++;
  }
}

int main()
{
  setlocale(LC_ALL, "ru");
  try
  {
    std::cout << "If you want to know about commands, please write --help\n";
    std::string commandHelp;
    //std::cin >> commandHelp;
    mainDict map;
    mainDict map2;
    std::fstream file("in.txt");
    std::fstream file2("in2.txt");
    inputDict(file, map);
    inputDict(file2, map2);
    //print(map, std::cout);
    printHelp();
    std::string dog = "save.txt";
    //find(map, dog, std::cout);
    //deleteWord(map, dog);
    mainDict map3;
    //int a = randomNumber(10, 900);
    //map3 = search(map3, map, map2, std::cin);
    //random(map3, 5, map, map2);
    editTranslation(map2, std::cin);
    save(map2, dog);
    //print(map3, std::cout);
    //save(map, dog, std::cin);
    if (commandHelp == "--help")
    {
      std::cout << "find - parameters < dict name >, < word >.\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << '\n';
    return 1;
  } 
}
