#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>

void allaberdiev::createDict(std::istream& in, std::map< std::string, std::map < std::string, std::vector< std::string > > >& dicts)
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

void allaberdiev::deleteDict(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  dicts.erase(name);
}