#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <stdexcept>

void addDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  std::map< std::string, std::vector< std::string > > new_dict;
  try
  {
    dictionaries.at(name);
  }
  catch (...)
  {
    dictionaries[name] = new_dict;
    return;
  }
  throw std::logic_error("<ALREADY EXISTS>");
}

void addWord(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  std::map< std::string, std::vector< std::string > > needed_dict = dictionaries.at(name);
}

int main()
{
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dictionaries;
  
  while (!std::cin.eof())
  {
    try
    {
      addDictionary(std::cin, dictionaries);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}