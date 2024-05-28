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

void removeWord(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
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
  in >> word;
  try
  {
    needed_dict.at(word);
  }
  catch (...)
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  needed_dict.erase(word);
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

void mergeDictionaries(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string first_name = "";
  std::string second_name = "";
  std::map< std::string, std::vector< std::string > > result;
  in >> first_name >> second_name;
  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& first = dictionaries[first_name];
  const std::map< std::string, std::vector< std::string > >& second = dictionaries[second_name];
  for (auto it = second.cbegin(); it != second.cend(); it++)
  {
    const std::string& key = it->first;
    const std::vector< std::string >& values = it->second;
    if (first.find(key) != first.end())
    {
      first[key].insert(first[key].end(), values.begin(), values.end());
    }
    else
    {
      first[key] = values;
    }
  }
}

int main()
{
  std::setlocale(LC_ALL, "Russian");
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dictionaries;
  using cmd_func = std::function< void(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&) >;
  std::map< std::string, cmd_func > cmds;
  {
    using namespace std::placeholders;
    cmds["new"] = addDictionary;
    cmds["delete"] = deleteDictionary;
    cmds["add"] = addWord;
    cmds["translate"] = std::bind(translate, std::ref(std::cout), _1, _2);
    cmds["remove"] = removeWord;
    cmds["merge"] = mergeDictionaries;
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd_name = "";
      std::cin >> cmd_name;
      cmds.at(cmd_name)(std::cin, dictionaries);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}