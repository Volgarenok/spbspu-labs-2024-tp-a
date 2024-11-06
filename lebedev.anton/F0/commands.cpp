#include "commands.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <vector>

bool dictSortComparator(const std::pair< std::string, size_t > & p1, const std::pair< std::string, size_t > & p2)
{
  return p1.second > p2.second;
}

std::vector< std::pair< std::string, size_t > > sortDictionary(const std::map< std::string, size_t > & dict)
{
  std::vector< std::pair< std::string, size_t > > sorted_dict(dict.begin(), dict.end());
  std::sort(sorted_dict.begin(), sorted_dict.end(), dictSortComparator);
  return sorted_dict;
}

std::string formOutputPair(std::pair< std::string, size_t > pair)
{
  return (pair.first + " -- " + std::to_string(pair.second));
}

void addWord(lebedev::Dictionary & dict, const std::pair< std::string, size_t > & pair)
{
  dict.recordWord(pair.first, pair.second);
}

lebedev::Dictionary unionDicts(const std::map< std::string, size_t > & dict1, const std::map< std::string, size_t > & dict2)
{
  lebedev::Dictionary result_dict;
  using namespace std::placeholders;
  std::for_each(dict1.begin(), dict1.end(), std::bind(addWord, std::ref(result_dict), _1));
  std::for_each(dict2.begin(), dict2.end(), std::bind(addWord, std::ref(result_dict), _1));
  return result_dict;
}

bool isKey(std::pair< std::string, size_t > pair, size_t n)
{
  return pair.second == n;
}

void lebedev::doHelp(std::ostream & output)
{
  output << "List of available commands:\n";
  output << "1. readtext <text1> <dict1> -- Read text from file and create a dictionary\n";
  output << "2. find <dict1> <word1> -- Find word in dictionary and print it's number of uses\n";
  output << "3. delete <dict1> -- Delete dictionary\n";
  output << "4. printtopn <dict1> <N> -- Print N most common words in dictionary\n";
  output << "5. printantitopn <dict1> <N> -- Print N most rare words in dictionary\n";
  output << "6. print <dict1> -- Print all words from dictionary with their number of uses\n";
  output << "7. merge <dict1> <dict2> -- Add words from second dictionary to first\n";
  output << "8. union <dict1> <dict2> <dict> -- Creates a dictionary with words from both dictionaries\n";
  output << "9. expand <dict1> <text1> -- Add words from file to dictionary\n";
  output << "10. searchfreq <dict1> <freq1> -- Prints word with entered number of uses\n";
  output << "11. save <dict1> <file1> -- Save dictionary to file\n";
  output << "12. readdict <file1> <dict1> -- Restore dictionary fron file\n";
}

void lebedev::getReadtextCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string filename;
  std::string dictionary_name;
  input >> filename >> dictionary_name;
  std::ifstream inputf(filename);
  if (!input || !inputf || dictionaries.count(dictionary_name) == 1)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Dictionary curr_dict;
  inputf >> curr_dict;
  dictionaries.insert(std::pair< std::string, Dictionary >(dictionary_name, curr_dict));
  output << "Dictionary " << dictionary_name << " was successfully created!\n";
}

void lebedev::getFindCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  std::string word;
  input >> dict_name >> word;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  else
  {
    Dictionary curr_dict = dictionaries.at(dict_name);
    if (curr_dict.getDict().count(word) == 0)
    {
      throw std::invalid_argument("<NOT FOUND>");
    }
    else
    {
      size_t n = curr_dict.getDict().at(word);
      output << word << " -- " << n << "\n";
    }
  }
}

void lebedev::getDeleteCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  else
  {
    dictionaries.erase(dictionaries.find(dict_name));
    output << "Dictionary " << dict_name << " was successfully deleted!\n";
  }
}

void lebedev::getPrinttopnCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  size_t num = 0;
  input >> dict_name >> num;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > curr_dict = dictionaries.at(dict_name).getDict();
  std::vector< std::pair< std::string, size_t > > sorted_dict = sortDictionary(curr_dict);
  std::vector < std::string > sorted_dict_out;
  sorted_dict_out.reserve(sorted_dict.size());
  std::transform(sorted_dict.cbegin(), sorted_dict.cend(), std::back_inserter(sorted_dict_out), formOutputPair);
  if (sorted_dict.size() < num)
  {
    std::copy(sorted_dict_out.cbegin(), sorted_dict_out.cend(), std::ostream_iterator< std::string >(output, "\n"));
  }
  else
  {
    std::copy_n(sorted_dict_out.cbegin(), num, std::ostream_iterator< std::string >(output, "\n"));
  }
}

void lebedev::getPrintantitopnCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  size_t num = 0;
  input >> dict_name >> num;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > curr_dict = dictionaries.at(dict_name).getDict();
  std::vector< std::pair< std::string, size_t > > sorted_dict = sortDictionary(curr_dict);
  std::vector < std::string > sorted_dict_out;
  sorted_dict_out.reserve(sorted_dict.size());
  std::transform(sorted_dict.cbegin(), sorted_dict.cend(), std::back_inserter(sorted_dict_out), formOutputPair);
  std::reverse(sorted_dict_out.begin(), sorted_dict_out.end());
  if (sorted_dict.size() < num)
  {
    std::copy(sorted_dict_out.cbegin(), sorted_dict_out.cend(), std::ostream_iterator< std::string >(output, "\n"));
  }
  else
  {
    std::copy_n(sorted_dict_out.cbegin(), num, std::ostream_iterator< std::string >(output, "\n"));
  }
}

void lebedev::getPrintCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > curr_dict = dictionaries.at(dict_name).getDict();
  std::vector< std::pair< std::string, size_t > > sorted_dict = sortDictionary(curr_dict);
  std::vector < std::string > sorted_dict_out;
  sorted_dict_out.reserve(sorted_dict.size());
  std::transform(sorted_dict.cbegin(), sorted_dict.cend(), std::back_inserter(sorted_dict_out), formOutputPair);
  std::copy(sorted_dict_out.cbegin(), sorted_dict_out.cend(), std::ostream_iterator< std::string >(output, "\n"));
}

void lebedev::getMergeCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name1;
  std::string dict_name2;
  input >> dict_name1 >> dict_name2;
  if (!input || dictionaries.count(dict_name1) == 0 || dictionaries.count(dict_name2) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Dictionary dict1 = dictionaries.at(dict_name1);
  Dictionary dict2 = dictionaries.at(dict_name2);
  dict1 = unionDicts(dict1.getDict(), dict2.getDict());
  dictionaries.at(dict_name1) = dict1;
  output << "Dictionary " << dict_name2 << " was merged into " << dict_name1 << "!\n";
}

void lebedev::getUnionCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name1;
  std::string dict_name2;
  std::string res_dict_name;
  input >> dict_name1 >> dict_name2 >> res_dict_name;
  bool is_new = (dictionaries.count(res_dict_name) == 0);
  if (!input || dictionaries.count(dict_name1) == 0 || dictionaries.count(dict_name2) == 0 || !is_new)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Dictionary dict1 = dictionaries.at(dict_name1);
  Dictionary dict2 = dictionaries.at(dict_name2);
  Dictionary res_dict = unionDicts(dict1.getDict(), dict2.getDict());
  dictionaries.insert(std::pair< std::string, Dictionary >(res_dict_name, res_dict));
  output << "Dictionaries " << dict_name1 << " and " << dict_name2 << " were merged into " << res_dict_name << "!\n";
}

void lebedev::getExpandCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  std::string filename;
  input >> dict_name >> filename;
  std::ifstream inputf(filename);
  if (!input || !inputf || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Dictionary curr_dict;
  inputf >> curr_dict;
  dictionaries.at(dict_name) = unionDicts(dictionaries.at(dict_name).getDict(), curr_dict.getDict());
  output << "Dictionary " << dict_name << " was expanded with " << filename << "!\n";
}

void lebedev::getSearchfreqCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  size_t num = 0;
  input >> dict_name >> num;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > dict = dictionaries.at(dict_name).getDict();
  std::vector< std::pair< std::string, size_t > > sorted_dict = sortDictionary(dict);
  std::vector< std::pair< std::string, size_t > > sorted_dict_out;
  using namespace std::placeholders;
  std::copy_if(sorted_dict.cbegin(), sorted_dict.cend(), std::back_inserter(sorted_dict_out), std::bind(isKey, _1, num));
  std::vector < std::string > sorted_strs_out;
  std::transform(sorted_dict_out.begin(), sorted_dict_out.end(), std::back_inserter(sorted_strs_out), formOutputPair);
  std::copy(sorted_strs_out.cbegin(), sorted_strs_out.cend(), std::ostream_iterator< std::string >(output, "\n"));
}

void lebedev::getSaveCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  std::string filename;
  input >> dict_name >> filename;
  if (!input || dictionaries.count(dict_name) == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::ofstream outputf(filename);
  if (!outputf.is_open())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Dictionary dict = dictionaries.at(dict_name);
  std::vector< std::pair< std::string, size_t > > sorted_dict = sortDictionary(dict.getDict());
  for (const auto & pair : sorted_dict)
  {
    outputf << pair.first << " " << pair.second << "\n";
  }
  output << "Dictionary " << dict_name << " was saved to the file " << filename << "!\n";
}

void lebedev::getReaddictCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string filename;
  std::string dict_name;
  input >> filename >> dict_name;
  std::ifstream inputf(filename);
  if (!input || !inputf || dictionaries.count(dict_name) == 1)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::map< std::string, size_t > curr_dict;
  std::string word;
  size_t num = 0;
  while (inputf >> word >> num)
  {
    curr_dict.insert(std::make_pair(word, num));
  }
  dictionaries.insert(std::pair< std::string, Dictionary >(dict_name, Dictionary(curr_dict)));
  output << "Dictionary " << dict_name << " was read from the file " << filename << "!\n";
}
