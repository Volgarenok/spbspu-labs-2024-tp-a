#include <iostream>
#include <limits>
#include <scopeGuard.hpp>
#include "inputDictionary.hpp"

void zakozhurnikova::inputArgs(std::istream& in, std : list< std::string >& args)
{
  ScopeGuard guard(in);
  in >> std::noskipws;
  std::string tmp;
  char delim = 0;
  in >> delim;
  while (in && delim != '\n')
  {
    in >> tmp;
    if (in)
    {
      args.push_back(tmp);
    }
    in >> delim;
  }
}

bool isEnglish(const std::string& temp)
{
  if ((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z'))
  {
    return true;
  }
  return false;
}

void zakozhurnikova::inputDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::list< std::string > > >& maps)
{
  ScopeGuard guard(in);
  std::string nameDictionary;
  while (in)
  {
    std::string temp;
    in >> nameDictionary;
    std::string word;
    List< std::string > translate;
    BinarySearchTree< std::string, List< std::string > > translation;
    in >> std::noskipws;
    char space;
    in >> space;
    while (in && space != '\n')
    {
      in >> temp;
      if (isEnglish(temp) && word.empty())
      {
        word = temp;
      }
      else if (!isEnglish(temp) && !word.empty())
      {
        translate.push_back(temp);
      }
      else if (!word.empty() && !translate.empty())
      {
        translation.push(word, translate);
        word.clear();
        translate.clear();
        word = temp;
      }
      else
      {
        std::cout << "incorret(empty) input translate word: " << word << " - the word is not written in the dictionary";
      }
      in >> space;
    }
    if (!word.empty() && !translate.empty())
    {
      translation.push(word, translate);
    }
    if (!in.eof())
    {
      in.clear();
    }
    if (!translation.empty() && !nameDictionary.empty())
    {
      maps.push(nameDictionary, translation);
    }
    else if (!nameDictionary.empty())
    {
      std::cout << "The dictionary is empty:" << nameDictionary << '\n';
    }
  }
}
