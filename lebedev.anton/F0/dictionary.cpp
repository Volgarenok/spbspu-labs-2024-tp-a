#include "dictionary.hpp"

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
    curr_dict.recordWord(word);
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
