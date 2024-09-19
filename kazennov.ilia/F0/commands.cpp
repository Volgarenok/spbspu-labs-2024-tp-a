#include "commands.h"

#include <string>
#include <exception>
#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>
#include <execution>
#include <fstream>


void kazennov::add_word(std::istream & in, std::map< std::string, FrequencyDict >&mapOfDicts)
{
  std::string word;
  std::string dictionary;
  in >> word >> dictionary;
  if (word == "" || dictionary == "")
  {
    throw std::invalid_argument("invalid argument");
    return;
  }
  if (mapOfDicts.find(dictionary) == mapOfDicts.end())
  {
    FrequencyDict temp;
    temp.dict_.insert(std::pair< std::string, unsigned int >(word, 1));
    mapOfDicts.insert(std::pair< std::string, FrequencyDict >(dictionary, temp));
  }
  else
  {
    if (mapOfDicts.find(dictionary)->second.dict_.find(word) == mapOfDicts.find(dictionary)->second.dict_.end())
    {
      mapOfDicts.find(dictionary)->second.dict_.insert(std::pair<std::string, unsigned int>(word, 1));
    }
    else
    {
      mapOfDicts.find(dictionary)->second.dict_.find(word)->second++;
    }
  }
}

void add_wordForFile(std::string word, kazennov::FrequencyDict& dict)
{
  if (word != "")
  {
    if (dict.dict_.find(word) == dict.dict_.end())
    {
      dict.dict_.insert(std::pair<std::string, unsigned int>(word, 1));
    }
    else
    {
      dict.dict_.find(word)->second++;
    }
  }
}


void kazennov::add_from_file(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  std::string file;
  std::string dictionary;
  in >> file >> dictionary;
  if (file == "" || dictionary == "")
  {
    throw std::invalid_argument("invalid argument");
  }
  if (mapOfDicts.find(dictionary) == mapOfDicts.end())
  {
    FrequencyDict temp;
    std::ifstream f(file);
    if (f.is_open())
    {
      std::string line;
      std::string word = "";
      while (std::getline(f, line))
      {
        std::transform(line.begin(), line.end(), line.begin(), std::tolower);
        std::transform(line.begin(), line.end(), line.begin(), [](char t) {if ((int)t < 97 || (int)t > 122)
        return ' ';
        else return t; });
        std::for_each(line.begin(), line.end(), [&](char t) {if ((int)t != 32) word += t;
        else { add_wordForFile(word, temp); word = ""; }});
      }
    }
    mapOfDicts.insert(std::pair< std::string, FrequencyDict >(dictionary, temp));
  }
  else
  {
    std::ifstream f(file);
    if (f.is_open())
    {
      std::string line;
      std::string word;
      while (std::getline(f, line))
      {
        std::transform(line.begin(), line.end(), line.begin(), std::tolower);
        std::transform(line.begin(), line.end(), line.begin(), [](char t) {if ((int)t < 97 || (int)t > 122)
        return ' ';
        else return t; });
        std::for_each(line.begin(), line.end(), [&](char t) {
        if ((int)t != 32 && word.size() != 0) word.push_back(t);
        else { add_wordForFile(word, mapOfDicts.find(dictionary)->second); word = ""; }});
      }
    }
  }
}

void kazennov::get_frequency(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  std::string word;
  std::string dictionary;
  in >> word >> dictionary;
  if (word == "" || dictionary == "")
  {
    throw std::invalid_argument("invalid argument");
  }
  if (mapOfDicts.find(dictionary) == mapOfDicts.end())
  {
    throw std::invalid_argument("no dictionary with name: " + dictionary);
  }
  else
  {
    if (mapOfDicts.find(dictionary)->second.dict_.find(word) == mapOfDicts.find(dictionary)->second.dict_.end())
    {
      throw std::invalid_argument("no word in dictionary");
    }
    else
    {
      out << mapOfDicts.find(dictionary)->second.dict_.find(word)->second;
    }
  }
}

void kazennov::delete_word(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  std::string word;
  std::string dictionary;
  in >> word >> dictionary;
  if (word == "" || dictionary == "")
  {
    throw std::invalid_argument("invalid argument");
  }
  if (mapOfDicts.find(dictionary) == mapOfDicts.end())
  {
    throw std::invalid_argument("no dictionary with name: " + dictionary);
  }
  else
  {
    if (mapOfDicts.find(dictionary)->second.dict_.find(word) == mapOfDicts.find(dictionary)->second.dict_.end())
    {
      throw std::invalid_argument("no word in dictionary");
    }
    else
    {
      mapOfDicts.find(dictionary)->second.dict_.erase(word);
    }
  }
}

void kazennov::delete_dictionary(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  std::string dictionary;
  in >> dictionary;
  if (dictionary == "")
  {
    throw std::invalid_argument("invalid argument");
  }
  if (mapOfDicts.find(dictionary) == mapOfDicts.end())
  {
    throw std::invalid_argument("no dictionary with name: " + dictionary);
  }
  else
  {
    mapOfDicts.erase(dictionary);
  }
}


void kazennov::get_word_with_highest_frequency(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  VectorOfDicts input;
  std::vector<std::string> strInput;
  std::vector<std::pair<std::string, unsigned int>> searchingDicts;
  in >> input;
  std::transform(input.words_.begin(), input.words_.end(), std::back_inserter(strInput),
  [](WordForInput w) {return w.word_; });
  std::function<bool(std::pair<std::string, unsigned int> p, std::pair<std::string, unsigned int> other)> compare;
  auto log = [](std::pair<std::string, unsigned int> p, std::pair<std::string, unsigned int> other)
  {return p.second > other.second; };
  compare = log;
  std::transform(strInput.begin(), strInput.end(), std::back_inserter(searchingDicts), [&](std::string name) {
  if (mapOfDicts.find(name) == mapOfDicts.end())
  {
    throw std::invalid_argument("no dictionary with name: " + name);
  }
  else
  {
    return *std::max_element(mapOfDicts.find(name)->second.dict_.begin(), mapOfDicts.find(name)->second.dict_.end(), compare);
  }});
  out << std::max_element(searchingDicts.begin(), searchingDicts.end(), compare)->first << ": ";
  out << std::max_element(searchingDicts.begin(), searchingDicts.end(), compare)->second;
}

void kazennov::get_count_of_word(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  std::string word;
  in >> word;
  VectorOfDicts input;
  std::vector<std::string> strInput;
  std::vector<std::pair<std::string, unsigned int>> searchingDicts;
  std::vector<int> Frequencies;
  in >> input;
  std::transform(input.words_.begin(), input.words_.end(), std::back_inserter(strInput), [](WordForInput w)
  {return w.word_; });
  std::transform(strInput.begin(), strInput.end(), std::back_inserter(searchingDicts), [&](std::string name) {
  if (mapOfDicts.find(name) == mapOfDicts.end())
  {
    throw std::invalid_argument("no dictionary with name: " + name);
  }
  else
  {
    if (mapOfDicts.find(name)->second.dict_.find(word) != mapOfDicts.find(name)->second.dict_.end())
      return std::pair< std::string, unsigned int >(word, mapOfDicts.find(name)->second.dict_.find(word)->second);
    else
      return std::pair< std::string, unsigned int >("", 0);
  }});
  std::transform(searchingDicts.begin(), searchingDicts.end(), std::back_inserter(Frequencies), [](std::pair<std::string, unsigned int> t)
  {return t.second; });
  out << std::accumulate(Frequencies.begin(), Frequencies.end(), 0);
}



void kazennov::intersection(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts)
{
  std::string firstDict;
  std::string secondDict;
  in >> firstDict >> secondDict;
  if (firstDict == "" || secondDict == "" || mapOfDicts.find(firstDict) == mapOfDicts.end() || mapOfDicts.find(secondDict) == mapOfDicts.end())
  {
    throw std::invalid_argument("invalid argument");
  }
  else
  {
    FrequencyDict intersection;
    FrequencyDict intersectionRes;
    auto first = mapOfDicts.find(firstDict)->second.dict_;
    std::function< std::pair< std::string, unsigned int >(std::pair< std::string, unsigned int >) > isInDict;
    auto log = [&](std::pair< std::string, unsigned int > t) {
    if (mapOfDicts.find(secondDict)->second.dict_.find(t.first) != mapOfDicts.find(secondDict)->second.dict_.end())
      return std::pair< std::string, unsigned int >(t.first, t.second + mapOfDicts.find(secondDict)->second.dict_.find(t.first)->second);
    else
      return std::pair< std::string, unsigned int >("", 0);
    };
    isInDict = log;
    std::transform(first.begin(), first.end(), std::inserter(intersection.dict_, intersection.dict_.begin()), isInDict);
    std::copy_if(intersection.dict_.begin(), intersection.dict_.end(), std::inserter(intersectionRes.dict_, intersectionRes.dict_.begin()),
    [](auto const& t) { return t.second != 0; });
    std::string newDictName = "intersectionOf" + firstDict + "and" + secondDict;
    mapOfDicts.insert_or_assign(newDictName, intersectionRes);
  }
}


void kazennov::output(std::istream& in, std::ostream& out, std::map< std::string, FrequencyDict >& mapOfDicts)
{
  std::string dictionary;
  in >> dictionary;
  if (dictionary == "")
  {
    throw std::invalid_argument("invalid argument");
  }
  if (mapOfDicts.find(dictionary) == mapOfDicts.end())
  {
    throw std::invalid_argument("no dictionary with name: " + dictionary);
  }
  else
  {
    auto temp = mapOfDicts.find(dictionary)->second.dict_;
    std::for_each(temp.begin(), temp.end(), [&](const std::pair< std::string, unsigned int>& t)
    {out << t.first << ": " << t.second << '\n'; });
  }
}


