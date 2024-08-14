#include "additionalcommands.hpp"
#include <algorithm>
#include <functional>

bool kuznetsov::check_word(std::string& word)
{
  size_t size = 0;
  while (size != word.length())
  {
    if (!std::isalpha(word[size]))
    {
      return false;
    }
    ++size;
  }
  return true;
}

bool kuznetsov::sort_for_data_word(data_word& a, data_word& b)
{
  return a.second > b.second;
}
bool kuznetsov::is_equal_for_data_word(data_word a, data_word b)
{
  return a.first == b.first;
}

std::vector< data_word > kuznetsov::return_top_words(std::vector< frequency_dictionary >& dictionaries)
{
  std::vector< data_word > arr;
  for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
  {
    std::map< std::string, size_t > words = *it;
    for (auto it2 = words.begin(); it2 != words.end(); ++it2)
    {
      auto operation = std::bind(is_equal_for_data_word, std::placeholders::_1, (*it2));
      auto current = std::find_if(arr.begin(), arr.end(), operation);
      if (current != arr.end())
      {
        (*current).second += (*it2).second;
      }
      else
      {
        arr.push_back(*it2);
      }
    }
  }
  std::sort(arr.begin(), arr.end(), sort_for_data_word);
  return arr;
}
