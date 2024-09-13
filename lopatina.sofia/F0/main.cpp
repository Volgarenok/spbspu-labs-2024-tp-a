#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <exception>
#include <limits>
#include <algorithm>
#include <iterator>

void doHelp(std::ostream & out)
{
  out << "Command system:\n";
  out << "1. create <dictionary> <file> - Creates a frequency dictionary for a text file.\n";
  out << "2. print <dictionary> <key> - Outputs the frequency of occurrence of the word.\n";
  out << "3. print <dictionary> - Outputs a frequency dictionary.\n";
  out << "4. sort <dictionary> - Sorts the dictionary by the frequency of occurrence of words (from more to less frequent).\n";
  out << "5. delete <dictionary> <key> -  Deletes a word from the frequency dictionary.\n";
  out << "6. delete <dictionary> - Deletes the frequency dictionary.\n";
  out << "7. compare <dictionary1> <dictionary2> - Compares two dictionaries, returns 1 if they are the same or 0 if they are not.\n";
  out << "8. combine <dictionary1> <dictionary2> <dictionary to combine> - Combines two frequency dictionaries into a created dictionary.\n";
  out << "9. intersect <dictionary1> <dictionary2> <dictionary to intersect> - Creates a frequency dictionary from the intersection of two dictionaries.\n";
  out << "10. subtract <dictionary1> <dictionary2> <dictionary to subtract> - Creates a dictionary from words in the first dictionary that are not in the second dictionary.\n";
  out << "11. mostfrequent <dictionary> <amount> - Outputs the given number of the most frequently occurring words from the dictionary.\n";
}

class Dictionary
{
public:
  Dictionary() = default;
  Dictionary(const std::map< std::string, size_t > & dict):
    words_(dict)
  {}
  ~Dictionary() = default;

  void addWord(const std::string & word, const int & num = 1)
  {
    auto iter = words_.find(word);
    if (iter != words_.end())
    {
      (*iter).second += num;
      return;
    }
    words_.insert(std::pair< std::string, size_t >(word, num));
  }

  void deleteWord(const std::string & word)
  {
    auto iter = words_.find(word);
    if (iter != words_.end())
    {
      words_.erase(iter);
    }
  }

  bool checkWord(const std::string & word)
  {
    if (words_.find(word) != words_.end())
    {
      return true;
    }
    return false;
  }

  std::map< std::string, size_t > getDict() const
  {
    return words_;
  }

  std::map< std::string, size_t > & getDict()
  {
    return words_;
  }

private:
  std::map< std::string, size_t > words_;
};

std::istream & operator>>(std::istream & in, Dictionary & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Dictionary dict;
  std::string word;
  while (in >> word)
  {
    dict.addWord(word);
  }
  if (in.eof())
  {
    dest = dict;
  }
  return in;
}

void createCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dictionary_name = "", file_name = "";
  in >> dictionary_name >> file_name;
  std::ifstream input(file_name);
  if (!in || !input || dictionaries.count(dictionary_name) == 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Dictionary new_dict;
  input >> new_dict;
  dictionaries.insert(std::pair< std::string, Dictionary >(dictionary_name, new_dict));
}

std::string makeString(std::pair< std::string, size_t > dict_elem)
{
  return (dict_elem.first + ": " + std::to_string(dict_elem.second));
}

void printCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out)
{
  std::string dictionary_name = "", key_name = "";
  in >> dictionary_name;
  if (!in || dictionaries.find(dictionary_name) == dictionaries.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict_to_print = dictionaries.at(dictionary_name).getDict();
  in >> key_name;
  if (in)
  {
    if (dict_to_print.find(key_name) != dict_to_print.end())
    {
      out << dict_to_print.at(key_name) << '\n';
      return;
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  else
  {
    std::vector< std::string > to_out;
    std::transform(dict_to_print.begin(), dict_to_print.end(), std::back_inserter(to_out), makeString);
    std::copy(std::begin(to_out), std::end(to_out), std::ostream_iterator< std::string >(std::cout, "\n"));
  }
}

/*
void sortCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::map< std::string, int >()
}
*/
void deleteCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dictionary_name = "", key_name = "";
  in >> dictionary_name;
  if (!in || dictionaries.count(dictionary_name) == 0)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  in >> key_name;
  if (in)
  {
    if (dictionaries.at(dictionary_name).checkWord(key_name))
    {
      dictionaries.at(dictionary_name).deleteWord(key_name);
      return;
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  else
  {
    dictionaries.erase(dictionary_name);
  }
}

void compareCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out)
{
  std::string dict1_name = "", dict2_name = "";
  in >> dict1_name >> dict2_name;
  if (!in || dictionaries.count(dict1_name) == 0 || dictionaries.count(dict2_name) == 0)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (dictionaries.at(dict1_name).getDict() == dictionaries.at(dict2_name).getDict())
  {
    out << "1\n";
  }
  else
  {
    out << "0\n";
  }
}

void doCombine(Dictionary & dict, const std::pair<std::string, size_t> & pair)
{
    dict.addWord(pair.first, pair.second);
}

void combineCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dict1_name = "", dict2_name = "", combine_dict_name = "";
  in >> dict1_name >> dict2_name >> combine_dict_name;
  if (!in || dictionaries.count(dict1_name) == 0 || dictionaries.count(dict2_name) == 0 ||  dictionaries.count(combine_dict_name) == 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict1 = dictionaries.at(dict1_name).getDict();
  std::map< std::string, size_t > dict2 = dictionaries.at(dict2_name).getDict();
  Dictionary new_dict(dict1);
  using namespace std::placeholders;
  std::for_each(dict2.begin(), dict2.end(), std::bind(doCombine, std::ref(new_dict), _1));
  dictionaries.insert(std::pair<std::string, Dictionary>(combine_dict_name, new_dict));
}

/*
void intersectCmd(dicts & map_of_dict, std::istream & in)
{
  //это вроде пересечение/ создать предикат? который сравнивал бы элементы
  //идти по одному словарю и вставлять в новый словарь только те элементы которые есть и во втором
}

void subtractCmd(dicts & map_of_dict, std::istream & in)
{
  //вычитание второго из первого
  //использовать инверсию предиката из intersect?
}

void mostfrequentCmd(dicts & map_of_dict, std::istream & in)
{
  //можно создать копию словаря сделать sort и просто вывести необходимое количество
}
*/

int main(int argc, char ** argv)
{
  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    doHelp(std::cout);
  }
  else if (argc == 3 && std::string(argv[1]) == "--check")
  {
    std::ifstream input(argv[2]);
    if (!input)
    {
      std::cout << "No such file\n";
    }
    else
    {
      std::cout << "Such file exist";
      if (input.peek() == std::ifstream::traits_type::eof())
      {
        std::cout << ", but it's empty";
      }
      std::cout << '\n';
    }
  }
  else if (argc != 1)
  {
    std::cerr << "Wrong arguments\n";
    return 1;
  }

  std::map< std::string, Dictionary > dictionaries;
  std::map< std::string, std::function< void(std::map< std::string, Dictionary > &, std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["create"] = std::bind(createCmd, _1, _2);
    cmds["print"] = std::bind(printCmd, _1, _2, _3);
    //cmds["sort"] = std::bind(sortCmd, _1, _2);
    cmds["delete"] = std::bind(deleteCmd, _1, _2);
    cmds["compare"] = std::bind(compareCmd, _1, _2, _3);
    cmds["combine"] = std::bind(combineCmd, _1, _2);
    //cmds["intersect"] = std::bind(intersectCmd, map_of_dict, _1);
    //cmds["subtract"] = std::bind(subtractCmd, map_of_dict, _1);
    //cmds["mostfrequent"] = std::bind(mostfrequentCmd, map_of_dict, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      std::string str;
      std::getline(std::cin, str);
      std::istringstream iss(str);
      if (cmds.find(cmd) != cmds.end())
      {
        cmds.at(cmd)(dictionaries, iss, std::cout);
      }
      else
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
    catch (const std::exception & e)
    {
      std::cout << e.what() << '\n';
    }
  }
  return 0;

}
