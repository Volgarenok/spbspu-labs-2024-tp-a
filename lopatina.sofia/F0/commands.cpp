#include "commands.hpp"
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <exception>

void lopatina::doHelp(std::ostream & out)
{
  out << "Command system:\n";
  out << "1. create <dictionary> <file> - Creates a frequency dictionary for a text file.\n";
  out << "2. print <dictionary> <key> - Outputs the frequency of occurrence of the word.\n";
  out << "3. print <dictionary> - Outputs a frequency dictionary.\n";
  out << "4. sort <dictionary> - Sorts the dictionary by the frequency of occurrence of words (from more to less frequent) and outputs it.\n";
  out << "5. delete <dictionary> <key> -  Deletes a word from the frequency dictionary.\n";
  out << "6. delete <dictionary> - Deletes the frequency dictionary.\n";
  out << "7. compare <dict1> <dict2> - Compares two dictionaries, returns 1 if they are the same or 0 if they are not.\n";
  out << "8. combine <dict1> <dict2> <dict to combine> - Combines two frequency dictionaries into a created dictionary.\n";
  out << "9. intersect <dict1> <dict2> <dict to intersect> - Creates a dictionary from the intersection of two dictionaries.\n";
  out << "10. subtract <dict1> <dict2> <dict to subtract> - Creates a dictionary from words in the dict1 that are not in the dict2.\n";
  out << "11. mostfrequent <dictionary> <amount> - Outputs the given number of the most frequently occurring words from the dictionary.\n";
}

void lopatina::createCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
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

template < typename Container >
void outputDict(const Container & dict, std::ostream & out)
{
  if (dict.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  std::vector< std::string > to_out;
  std::transform(dict.begin(), dict.end(), std::back_inserter(to_out), makeString);
  std::copy(to_out.begin(), to_out.end(), std::ostream_iterator< std::string >(out, "\n"));
}

void lopatina::printCmd(const std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out)
{
  std::string dictionary_name = "", key_name = "";
  in >> dictionary_name;
  if (!in || dictionaries.count(dictionary_name) == 0)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict_to_print = dictionaries.at(dictionary_name).getDict();
  in >> key_name;
  if (in)
  {
    if (dict_to_print.count(key_name) == 1)
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
    outputDict(dict_to_print, out);
  }
}

bool sortCompare(const std::pair< std::string, size_t > & pair1, const std::pair< std::string, size_t > & pair2)
{
  if (pair1.second == pair2.second)
  {
    return pair1.first < pair2.first;
  }
  return pair1.second > pair2.second;
}

std::vector< std::pair< std::string, size_t > > doSort(const std::map< std::string, size_t > & dict)
{
  std::vector< std::pair< std::string, size_t > > sorted_dict(dict.begin(), dict.end());
  std::sort(sorted_dict.begin(), sorted_dict.end(), sortCompare);
  return sorted_dict;
}

void lopatina::sortCmd(const std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out)
{
  std::string dictionary_name = "";
  in >> dictionary_name;
  if (!in || dictionaries.count(dictionary_name) == 0)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict = dictionaries.at(dictionary_name).getDict();
  std::vector< std::pair< std::string, size_t > > sorted_dict = doSort(dict);
  outputDict(sorted_dict, out);
}

void lopatina::mostfrequentCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out)
{
  std::string dictionary_name = "";
  size_t amount = 0;
  in >> dictionary_name >> amount;
  if (!in || dictionaries.count(dictionary_name) == 0)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (amount == 0)
  {
    return;
  }
  std::map< std::string, size_t > dict = dictionaries.at(dictionary_name).getDict();
  std::vector< std::pair< std::string, size_t > > sorted_dict = doSort(dict);
  if (amount >= sorted_dict.size())
  {
    outputDict(sorted_dict, out);
    return;
  }
  std::vector< std::pair< std::string, size_t > > most_freq_dict;
  std::copy_n(sorted_dict.begin(), amount, std::back_inserter(most_freq_dict));
  outputDict(most_freq_dict, out);
}

void lopatina::deleteCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
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

void lopatina::compareCmd(const std::map< std::string, Dictionary > & dictionaries, std::istream & in, std::ostream & out)
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

void addWordToDict(lopatina::Dictionary & dict, const std::pair< std::string, size_t > & pair)
{
    dict.addWord(pair.first, pair.second);
}

void deleteWordFromDict(lopatina::Dictionary & dict, const std::pair< std::string, size_t > & pair)
{
    dict.deleteWord(pair.first);
}

lopatina::Dictionary createCombinedDict(const std::map< std::string, size_t > & dict1, const std::map< std::string, size_t > & dict2)
{
  lopatina::Dictionary new_dict(dict1);
  using namespace std::placeholders;
  std::for_each(dict2.begin(), dict2.end(), std::bind(addWordToDict, std::ref(new_dict), _1));
  return new_dict;
}

void lopatina::combineCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dict1_name = "", dict2_name = "", combine_dict_name = "";
  in >> dict1_name >> dict2_name >> combine_dict_name;
  if (!in || dictionaries.count(dict1_name) == 0 || dictionaries.count(dict2_name) == 0 ||  dictionaries.count(combine_dict_name) == 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict1 = dictionaries.at(dict1_name).getDict();
  std::map< std::string, size_t > dict2 = dictionaries.at(dict2_name).getDict();
  Dictionary new_dict = createCombinedDict(dict1, dict2);
  dictionaries.insert(std::pair< std::string, Dictionary >(combine_dict_name, new_dict));
}

bool isUnique(const std::pair< std::string, size_t > & dict_elem, const std::map< std::string, size_t > & dict_other)
{
  return dict_other.find(dict_elem.first) == dict_other.end();
}

void deleteUnique(lopatina::Dictionary & new_dict, const std::map< std::string, size_t > & dict_lhs, const std::map< std::string, size_t > & dict_rhs)
{
  std::map< std::string, size_t > unique_dict;
  using namespace std::placeholders;
  std::copy_if(dict_lhs.begin(), dict_lhs.end(), std::inserter(unique_dict, unique_dict.begin()), std::bind(isUnique, _1, dict_rhs));
  std::for_each(unique_dict.begin(), unique_dict.end(), std::bind(deleteWordFromDict, std::ref(new_dict), _1));
}

void lopatina::intersectCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dict1_name = "", dict2_name = "", intersect_dict_name = "";
  in >> dict1_name >> dict2_name >> intersect_dict_name;
  if (!in || dictionaries.count(dict1_name) == 0 || dictionaries.count(dict2_name) == 0 ||  dictionaries.count(intersect_dict_name) == 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict1 = dictionaries.at(dict1_name).getDict();
  std::map< std::string, size_t > dict2 = dictionaries.at(dict2_name).getDict();
  Dictionary new_dict = createCombinedDict(dict1, dict2);
  deleteUnique(new_dict, dict1, dict2);
  deleteUnique(new_dict, dict2, dict1);
  dictionaries.insert(std::pair< std::string, Dictionary >(intersect_dict_name, new_dict));
}

void lopatina::subtractCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dict1_name = "", dict2_name = "", subtract_dict_name = "";
  in >> dict1_name >> dict2_name >> subtract_dict_name;
  if (!in || dictionaries.count(dict1_name) == 0 || dictionaries.count(dict2_name) == 0 ||  dictionaries.count(subtract_dict_name) == 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict1 = dictionaries.at(dict1_name).getDict();
  std::map< std::string, size_t > dict2 = dictionaries.at(dict2_name).getDict();
  Dictionary new_dict(dict1);
  using namespace std::placeholders;
  std::for_each(dict2.begin(), dict2.end(), std::bind(deleteWordFromDict, std::ref(new_dict), _1));
  dictionaries.insert(std::pair< std::string, Dictionary >(subtract_dict_name, new_dict));
}
