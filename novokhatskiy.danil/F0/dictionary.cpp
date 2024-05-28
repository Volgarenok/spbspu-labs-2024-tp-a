#include "dictionary.hpp"
#include <stdexcept>

std::istream& novokhatskiy::operator>>(std::istream& in, Dictionary& dict)
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
      std::string tmp = {};
      std::getline(in, example);
      std::pair< std::string, std::set< std::string > > pair;
      pair.first = translation;

      for (size_t i = 0; example[i] != '\0'; i++)
      {
        tmp += example[i];
        if (example[i] == '.' || example[i] == '!' || example[i] == '?')
        {
          pair.second.insert(tmp);
          tmp = {};
        }
      }
      
      dict.dict_[word] = pair;
      in >> word;
    }
  }
  in.clear();
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Dictionary& dict)
{
  if (dict.dict_.empty())
  {
    throw std::logic_error("Empty dictionary");
  }
  for (auto i = dict.dict_.cbegin(); i != dict.dict_.cend(); i++)
  {
    std::cout << i->first << ' ' << i->second.first;
    for (auto j = i->second.second.cbegin(); j != i->second.second.cend(); j++)
    {
      std::cout << *j;
    }
    std::cout << '\n';
  }
  return out;
}
