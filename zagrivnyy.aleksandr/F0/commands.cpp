#include "commands.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

void zagrivnyy::help()
{
  std::cout << "Options:\n";
  std::cout << "\t--help\t\tprint this page\n";
  std::cout << "\t--check <file>\tcheck if the given file is correct\n\n";
  std::cout << "Commands:\n";
}

void zagrivnyy::check(const char *fileName)
{
  std::ifstream file(fileName);
  if (file.is_open())
  {
    std::cout << "Check: PASSED\n";
  }
  else
  {
    std::cout << "Check: FAILED\n";
  }
  file.close();
}

void zagrivnyy::read(dict_t &dictionaries, std::istream &in)
{
  std::string file = "";
  std::string dict_name = "";
  in >> file >> dict_name;

  zagrivnyy::Dictionary dictionary;

  std::fstream input(file);
  long unsigned int row = 0;
  while (!input.eof())
  {
    std::string line = "";
    std::getline(input, line);
    row++;

    std::stringstream ss(line);
    std::string word;
    long unsigned int col = 0;
    while (ss >> word)
    {
      col++;
      dictionary.add(word, {row, col});
    }
  }

  dictionaries[dict_name] = dictionary;
}

void zagrivnyy::list(const dict_t &dictionaries, std::istream &in, std::ostream &out)
{
  std::string dict_name = "";
  in >> dict_name;
  zagrivnyy::Dictionary dictionary;
  try
  {
    dictionary = dictionaries.at(dict_name);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }

  for (auto dict : dictionary.get_dict())
  {
    out << dict.first << ": \n";
    int count = 0;
    for (auto position : dict.second)
    {
      if (count == 0)
      {
        out << '\t';
      }

      out << position << ' ';
      count++;
      if (count == 20)
      {
        out << '\n';
        count = 0;
      }
    }
    out << '\n';
  }
}

void zagrivnyy::deleteDict(dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  in >> dict_name;
  dictionaries.erase(dict_name);
}

void zagrivnyy::merge(dict_t &dictionaries, std::istream &in)
{
  std::string newdict_name = "";
  std::string dict_name1 = "";
  std::string dict_name2 = "";
  in >> newdict_name >> dict_name1 >> dict_name2;

  if (dictionaries.find(newdict_name) != dictionaries.end())
  {
    throw std::invalid_argument("warn: dictionary name is already in use");
  }

  try
  {
    std::vector< std::vector< std::string > > dictionary1;
    std::vector< std::vector< std::string > > dictionary2;
    dictionary1 = dictionaries.at(dict_name1).generate_table();
    dictionary2 = dictionaries.at(dict_name2).generate_table();

    if (dictionary1.size() < dictionary2.size())
    {
      dictionary1.resize(dictionary2.size());
    }

    for (long unsigned int i = 0; i < dictionary2.size(); i++)
    {
      dictionary1[i].insert(dictionary1[i].end(), dictionary2[i].begin(), dictionary2[i].end());
    }

    zagrivnyy::Dictionary new_dictionary;
    new_dictionary.parse_table(dictionary1);
    dictionaries[newdict_name] = new_dictionary;
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }
}

void zagrivnyy::deleteWord(dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;

  try
  {
    zagrivnyy::Dictionary &dictionary = dictionaries.at(dict_name);
    dictionary.remove(word);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }
}

void zagrivnyy::find(const dict_t &dictionaries, std::istream &in, std::ostream &out)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;
  zagrivnyy::Dictionary dictionary;
  try
  {
    dictionary = dictionaries.at(dict_name);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }

  out << word << ": \n";
  int count = 0;
  for (auto position : dictionary.get(word))
  {
    if (count == 0)
    {
      out << '\t';
    }

    out << position << ' ';
    count++;
    if (count == 20)
    {
      out << '\n';
      count = 0;
    }
  }
  out << '\n';
}

void zagrivnyy::add(dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  std::string word = "";
  long unsigned int line = 0;
  in >> dict_name >> word >> line;
  try
  {
    zagrivnyy::Dictionary &dictionary = dictionaries.at(dict_name);
    std::vector< std::vector< std::string > > table = dictionary.generate_table();

    if (table.size() < line - 1)
    {
      table.resize(line);
    }
    table[line - 1].push_back(word);
    dictionary.parse_table(table);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }
}

void zagrivnyy::replace(dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  std::string word = "";
  std::string new_word = "";
  in >> dict_name >> word >> new_word;

  try
  {
    zagrivnyy::Dictionary &dictionary = dictionaries.at(dict_name);
    dictionary.add(new_word, dictionary.get(word));
    dictionary.remove(word);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }
}

void zagrivnyy::save(const dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  std::string file = "";
  in >> dict_name >> file;

  std::ofstream output(file);

  try
  {
    const zagrivnyy::Dictionary dictionary = dictionaries.at(dict_name);
    const std::vector< std::vector< std::string > > table = dictionary.generate_table();

    for (auto row : table)
    {
      for (auto word : row)
      {
        output << word << " ";
      }
      output << '\n';
    }
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }

  output.close();
}
