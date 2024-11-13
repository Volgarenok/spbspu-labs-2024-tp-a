#include "commands.hpp"
#include <sstream>
#include <exception>

#include <iostream>

namespace grechishnikov
{
  std::vector< std::string > parsStr(const std::string& str);
}

void grechishnikov::create(std::vector< Dictionary >& dicts, const std::string& param)
{
  auto pars = parsStr(param);
  if (pars.size() != 1)
  {
    throw std::logic_error("Icorrect number of parameters");
  }
  std::string name = pars[0];
  Dictionary temp(name);
  dicts.push_back(temp);
}

std::vector< std::string > grechishnikov::parsStr(const std::string& str)
{
  std::vector< std::string > strs;
  std::string word;
  std::stringstream strStream(str);
  while (getline(strStream, word, ' '))
  {
    if (!word.empty())
    {
      strs.push_back(word);
    }
  }
  return strs;
}
