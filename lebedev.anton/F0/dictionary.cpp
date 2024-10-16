#include "dictionary.hpp"

lebedev::Dictionary::Dictionary(const std::map< std::string, size_t > & dict):
  dict_(dict)
{}

void lebedev::Dictionary::recordWord(const std::string & word, const size_t & n)
{
  if (dict_.count(word) == 0)
  {
    dict_.insert(std::pair < std::string, size_t >(word, n));
  }
  else
  {
    dict_.at(word) += n;
  }
}

std::map< std::string, size_t > lebedev::Dictionary::getDict() const
{
  return dict_;
}

void clearExtraSymbols(std::string & str)
{
  while (!str.empty() && !std::isalnum(str.front()))
  {
    str.erase(str.begin());
  }
  while (!str.empty() && !std::isalnum(str.back()))
  {
    str.pop_back();
  }
}

std::istream & lebedev::operator>>(std::istream & input, Dictionary & dict)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Dictionary curr_dict;
  std::string word;
  while (input >> word)
  {
    clearExtraSymbols(word);
    if (!word.empty())
    {
      curr_dict.recordWord(word);
    }
  }
  if (input.eof())
  {
    dict = std::move(curr_dict);
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
