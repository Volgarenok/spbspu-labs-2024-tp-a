#include "Commands.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

void kuzmina::addWord(std::istream& in, Dict& dict)
{
  std::string word;
  in >> word;

  try
  {
    if (dict.count(word))
    {
      throw std::logic_error("This word is already in the dictionary");
    }

    dict[word] = std::vector< std::string >{};
  }
  catch (std::exception&)
  {
    throw std::invalid_argument("No such dictionary");
  }
}

void kuzmina::addTranslation(std::istream& in, Dict& dict)
{
  std::string word, translation;
  in >> word >> translation;

  try
  {
    if (!dict.count(word))
    {
      throw std::logic_error("No such word in the dictionary");
    }

    std::vector< std::string >& data = dict.at(word);

    if (std::find(data.cbegin(), data.cend(), translation) != data.cend())
    {
      throw std::logic_error("This word already has such translation");
    }

    dict.at(word).push_back(translation);
  }
  catch (std::logic_error& e)
  {
    throw std::logic_error(e.what());
  }
  catch (std::exception&)
  {
    throw std::invalid_argument("No such dictionary");
  }
}

//void kuzmina::searchWord(std::istream& in, std::ostream& out, const Dict& dict) {}
//void kuzmina::searchTranslation(std::istream& in, std::ostream& out, const Dict& dict) {}

//void kuzmina::deleteWord(std::istream& in, Dict& dict) {}
//void kuzmina::deleteTranslation(std::istream& in, Dict& dict) {}

//void kuzmina::findSynonyms(std::istream& in, std::ostream& out, Dict& dict) {}
//void kuzmina::countWords(std::istream& in, std::ostream& out, Dict& dict) {}

//void kuzmina::intersect(std::istream& in, allDicts& dicts) {}
//void kuzmina::subtract(std::istream& in, allDicts& dicts) {}
//void kuzmina::merge(std::istream& in, allDicts& dicts) {}

