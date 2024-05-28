#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
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

void deleteDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  try
  {
    dictionaries.at(name);
  }
  catch (...)
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  dictionaries.erase(name);
}

void addWord(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  std::map< std::string, std::vector< std::string > > needed_dict;
  try
  {
    needed_dict = dictionaries.at(name);
  }
  catch (...)
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::string word = "";
  std::string translation = "";
  in >> word >> translation;
  needed_dict[word].push_back(translation);
  dictionaries[name] = needed_dict;
}

void translate(std::ostream& out, std::istream& in, const std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  std::map< std::string, std::vector< std::string > > needed_dict;
  try
  {
    needed_dict = dictionaries.at(name);
  }
  catch (...)
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::string eng_word = "";
  in >> eng_word;
  std::vector< std::string > translations;
  try
  {
    translations = needed_dict.at(eng_word);
  }
  catch (...)
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator< std::string >(out, " "));
  out << "\n";
  return;
}

int main()
{
  std::setlocale(LC_ALL, "Russian");
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dictionaries;
  using cmd_func = std::function< void() >;
  std::map< std::string, cmd_func > cmds;
  {
    cmds["new"] = std::bind(addDictionary, std::ref(std::cin), std::ref(dictionaries));
    cmds["delete"] = std::bind(deleteDictionary, std::ref(std::cin), std::ref(dictionaries));
    cmds["add"] = std::bind(addWord, std::ref(std::cin), std::ref(dictionaries));
    cmds["translate"] = std::bind(translate, std::ref(std::cout), std::ref(std::cin), std::ref(dictionaries));
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd_name = "";
      std::cin >> cmd_name;
      cmds.at(cmd_name)();
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
  }
}