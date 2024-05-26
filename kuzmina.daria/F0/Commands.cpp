#include "Commands.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

bool hasTranslation(const std::vector< std::string >& data, const std::string& translation)
{
  return std::find(data.cbegin(), data.cend(), translation) != data.cend();
}

void kuzmina::addWord(std::istream& in, Dict& dict)
{
  std::string word;
  in >> word;

  if (dict.count(word))
  {
    throw std::logic_error("This word is already in the dictionary");
  }

  dict[word] = std::vector< std::string >{};
}

void kuzmina::addTranslation(std::istream& in, Dict& dict)
{
  std::string word, translation;
  in >> word >> translation;

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  if (hasTranslation(dict.at(word), translation))
  {
    throw std::logic_error("This word already has such translation");
  }

  dict.at(word).push_back(translation);
}

void kuzmina::searchWord(std::istream& in, std::ostream& out, const Dict& dict)
{
  std::string word;
  in >> word;

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  out << word << ": ";

  if (dict.at(word).size() == 0)
  {
    std::cout << "(no translationst added yet)";
  }
  else
  {
    using output_it_t = std::ostream_iterator< std::string >;
    std::copy(dict.at(word).cbegin(), dict.at(word).cend(), output_it_t{ out, " " });
  }
}

void kuzmina::searchTranslation(std::istream& in, std::ostream& out, const Dict& dict)
{
  std::string translation;
  in >> translation;

  std::vector< std::string > words;

  for (auto word_i : dict)
  {
    if (hasTranslation(word_i.second, translation))
    {
      words.push_back(word_i.first);
    }
  }

  if (words.size() == 0)
  {
    throw std::logic_error("No such translation");
  }
  else
  {
    out << translation << ": ";

    using output_it_t = std::ostream_iterator< std::string >;
    std::copy(words.cbegin(),words.cend(), output_it_t{ out, " " });
  }
}

void kuzmina::deleteWord(std::istream& in, Dict& dict)
{
  std::string word;
  in >> word;

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  dict.erase(word);
}

void kuzmina::deleteTranslation(std::istream& in, Dict& dict)
{
  std::string word, translation;
  in >> word >> translation;

  if (!dict.count(word))
  {
    throw std::logic_error("No such word");
  }

  if (!hasTranslation(dict.at(word), translation))
  {
    throw std::logic_error("No such translation");
  }

  auto translationIt = std::find(dict.at(word).cbegin(), dict.at(word).cend(), translation);
  dict.at(word).erase(translationIt);
}

//void kuzmina::findSynonyms(std::istream& in, std::ostream& out, Dict& dict) {}
//void kuzmina::countWords(std::istream& in, std::ostream& out, Dict& dict) {}

//void kuzmina::intersect(std::istream& in, allDicts& dicts) {}
//void kuzmina::subtract(std::istream& in, allDicts& dicts) {}
//void kuzmina::merge(std::istream& in, allDicts& dicts) {}
