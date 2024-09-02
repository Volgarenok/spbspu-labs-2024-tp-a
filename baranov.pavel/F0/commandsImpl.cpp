#include "commandsImpl.hpp"

void baranov::extendDict(dict_t & dict, std::istream & in)
{
  std::string word;
  while (in >> word)
  {
    std::string cleanWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
      char c = word[i];
      if (std::isalpha(c))
      {
        cleanWord += std::tolower(c);
      }
    }
    if (!cleanWord.empty())
    {
      dict[cleanWord]++;
    }
  }
}

void baranov::printElement(const pair_t & item, std::ostream & out)
{
  out << item.first << ' ' << item.second << '\n';
}

baranov::pair_t baranov::getCount(const std::pair< std::string, dict_t > & namedDict, const std::string & word)
{
  return std::make_pair(namedDict.first, getWordCount(namedDict.second, word));
}

size_t baranov::getWordCount(const dict_t & dict, const std::string & word)
{
  try
  {
    return dict.at(word);
  }
  catch (const std::out_of_range &)
  {
    return 0;
  }
}

bool baranov::countComparator(const pair_t & lhs, const pair_t & rhs)
{
  return lhs.second < rhs.second;
}

bool baranov::isContains(const dict_t & dict, const pair_t & item)
{
  auto it = dict.find(item.first);
  return it != dict.cend();
}

void baranov::joinWord(const pair_t & item, dict_t & dict)
{
  dict[item.first] += item.second;
}

baranov::pair_t baranov::addWordCount(const pair_t & item, const dict_t & dict)
{
  return std::make_pair(item.first, item.second + dict.at(item.first));
}

void baranov::printDictName(const std::pair< std::string, dict_t > & namedDict, std::ostream & out)
{
  out << namedDict.first << '\n';
}
