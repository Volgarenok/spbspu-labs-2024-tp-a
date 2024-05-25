#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <list>

using val_t = std::pair< std::string, std::list< std::string > >;
using mainDict = std::map< std::string, val_t >;

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
    std::fstream file("in.txt");
    inputDict(file, map);
    //print(map, std::cout);
    std::string dog = "fkl;saf;l";
    //find(map, dog, std::cout);
    deleteWord(map, dog);
    print(map, std::cout);
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
