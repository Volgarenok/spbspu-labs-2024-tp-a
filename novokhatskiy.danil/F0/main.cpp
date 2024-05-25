#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <windows.h>
#include <list>

using val_t = std::pair< std::string, std::list< std::string > >;
using mainDict = std::map< std::string, val_t >;

void save(const mainDict& dict, std::string& name, std::istream& in)
{
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
    std::string dog = "save.txt";
    //find(map, dog, std::cout);
    //deleteWord(map, dog);
    mainDict map3;
    map3 = merge(map, map2);
    print(map3, std::cout);
    save(map, dog, std::cin);
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
