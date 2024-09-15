#include "cmds.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>

void altun::createDictionary(std::istream& in, std::map< std::string, std::map < std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;

  if (dicts.find(name) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }

  std::map< std::string, std::vector< std::string > > newDict = {};
  dicts[name] = newDict;
}

void altun::deleteDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  dicts.erase(name);
}