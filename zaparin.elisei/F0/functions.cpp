#include "functions.hpp"

#include <fstream>
#include <algorithm>
#include "commands.hpp"

std::string zaparin::filter(std::string word)
{
  if (word.size() == 0)
  {
    return "";
  }

  char trash[9] = { '!', '?', ',', '.', '"', '\'', '-', '(', ')' };

  for (size_t i = 0; i < 9; i++)
  {
    if (trash[i] == word[0])
    {
      if (word.size() == 1)
      {
        return "";
      }
      word = word.substr(1);
    }
    if (trash[i] == word[word.size() - 1])
    {
      word = word.substr(0, word.size() - 1);
      break;
    }
  }

  std::transform(word.begin(), word.end(), word.begin(), tolower);
  return word;
}

bool zaparin::loadFile(Dict& dict, std::string& filename)
{
  std::ifstream fin;
  fin.open(filename);

  if (!fin.is_open())
  {
    throw std::logic_error("file is not opened\n");
  }

  std::string str;
  while (fin >> str)
  {
    str = filter(str);
    if (str != "")
    {
      dict[str]++;
    }
  }

  fin.close();

  return 1;
}

size_t zaparin::getNumOfWords(Dict& dict)
{
  size_t numOfWords = 0;

  Dict::iterator it_begin = dict.begin();
  Dict::iterator it_end = dict.end();

  while (it_begin != it_end)
  {
    numOfWords += it_begin->second;

    it_begin++;
  }

  return numOfWords;
}

bool zaparin::contains(Dict& dict, std::pair< const std::string, size_t >& elem)
{
  return dict.count(elem.first);
}

bool zaparin::not_contains(Dict& dict, std::pair< const std::string, size_t >& elem)
{
  return !(dict.count(elem.first));
}

bool zaparin::compare(const std::pair< const std::string, size_t >& elem1, const std::pair< const std::string, size_t >& elem2)
{
  return (elem1.second < elem2.second);
}

void zaparin::saveDict(Dict& dict, std::ostream& out)
{
  Dict::iterator it_begin = dict.begin();
  Dict::iterator it_end = dict.end();

  while (it_begin != it_end)
  {
    out << " " << it_begin->first << " " << it_begin->second;

    it_begin++;
  }
  out << "\n";
}

void zaparin::loadDict(Dict& dict, std::istream& in)
{
  std::string word;
  size_t numOfWords;

  while (in.peek() != '\n')
  {
    in >> word >> numOfWords;

    dict.insert({ word, numOfWords });
  }
}

