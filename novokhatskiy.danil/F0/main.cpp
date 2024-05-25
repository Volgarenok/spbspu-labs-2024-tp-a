#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <list>

using val_t = std::pair< std::string, std::list< std::string > >;
using mainDict = std::map< std::string, val_t >;

void find(const mainDict& dict, std::string& key)
{

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
  auto begin = dict.cbegin();
  while (begin != dict.cend())
  {
    out << begin->first << ' ' << begin->second.first << ' ' << begin->second.second.front() << '\n';
    begin++;
  }
  out << '\n';
}

int main()
{
  setlocale(LC_ALL, "ru");
  std::cout << "If you want to know about commands, please write --help\n";
  std::string commandHelp;
  //std::cin >> commandHelp;
  mainDict map;
  std::fstream file("in.txt");
  inputDict(file, map);
  print(map, std::cout);
  if (commandHelp == "--help")
  {
    std::cout << "find - parameters < dict name >, < word >.\n";
  }
}
