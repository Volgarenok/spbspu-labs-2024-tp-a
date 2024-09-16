#include "commands.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

void kartamyshev::help(std::ostream& out)
{
  out << "List of commands\n";
  out << " - create <name> - create new dictioanry\n";
  out << " - fill_in <file.txt> <name> - fill dictionary from file\n";
  out << " - list_information <name> - display dictionary information\n";
  out << " - search <word> <name> - search word in dictionary\n";
  out << " - delete_dictionary <name> - delete dictionary\n";
  out << " - merge <name 1> <name 2> - enter the data of the second dictionary into the first\n";
  out << " - get_merge <name 1> <name 2> <name 3> - merge two dictionaries into an existing third one\n";
  out << " - list_popular <name> <count> - display the number of popular words\n";
  out << " - get_intersection <name 1> <name 2> <name 3> - create a third dictionary and enter the data of the first and second into it\n";
  out << " - list_rare <name> <count> -  display the number of rare words\n";
  out << " - clear <name> - clear dictionary\n";
  out << " - list_range_words <name> <count> <count> - display the range words\n";
}


void kartamyshev::create(DictionarySet& set, std::istream& in)
{
  std::string name;
  in >> name;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }
  if (set.count(name) > 0)
  {
    throw std::logic_error("<DICTIOARY EXISTS>");
  }
  set[name];
}

void kartamyshev::insert(DictionarySet& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;

  ++collection.at(dict)[word];
}


void kartamyshev::fill_in(DictionarySet& set, std::istream& in)
{
  std::string name;
  in >> name;
  std::string fileName;
  in >> fileName;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }
  if (set.count(name) == 0)
  {
    set[name];
  }
  std::fstream file(fileName);
  if (!file.is_open() || file.peek() == EOF)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  std::string word;
  while (!file.eof())
  {
  file >> word;
  ++set.at(name)[word];
  }
}

std::string getStr(const std::pair<std::string, size_t>& pair)
{
  return pair.first + ": " + std::to_string(pair.second);
}

void kartamyshev::list_information(DictionarySet& set, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }
  if (set.count(name) == 0)
  {
    throw std::logic_error("<DICTIONARY DOES NOT EXIST>");
  }
  if (set.at(name).empty())
  {
    throw std::logic_error("DICTIONARY EMPTY\n");
  }
  std::transform(set.at(name).cbegin(), set.at(name).cend(),
    std::ostream_iterator< const std::string& >(std::cout, "\n"), getStr);
}

void kartamyshev::search(DictionarySet& set, std::istream& in, std::ostream& out)
{
  std::string word;
  std::string name;
  in >> word >> name;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>\n");
  }
  if (set.at(name).count(word) == 0)
  {
    throw std::logic_error("<WORD NOT FOUND>\n");
  }
  else
  {
    out << set.at(name)[word];
  }
}

void kartamyshev::delete_dictionary(DictionarySet& set, std::istream& in)
{
  std::string name;
  in >> name;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>\n");
  }
  if (set.count(name) == 0)
  {
  throw std::logic_error("<DICTIONARY DOES NOT EXIST>\n");
  }
  set.erase(name);
}

bool copyOrIncreaseFrequency(kartamyshev::FrequencyDictionary& set3, const std::pair< std::string, size_t >& pair)
{
  if (set3.find(pair.first) == set3.end())
  {
  return true;
  }
  set3[pair.first] += pair.second;
  return false;
}

void kartamyshev::merge(DictionarySet& set, std::istream& in)
{
  std::string set1;
  std::string set2;

  in >> set1 >> set2;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }

  std::copy_if(set.at(set2).cbegin(), set.at(set2).cend(), std::inserter(set[set1], set[set1].begin()),
    std::bind(copyOrIncreaseFrequency, std::ref(set[set1]), std::placeholders::_1));

}

void kartamyshev::get_merge(DictionarySet& set, std::istream& in)
{
  std::string set3;
  std::string set1;
  std::string set2;

  in >> set3 >> set1 >> set2;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }

  std::copy(set.at(set1).cbegin(), set.at(set1).cend(), std::inserter(set[set3], set[set3].begin()));
  std::copy_if(set.at(set2).cbegin(), set.at(set2).cend(), std::inserter(set[set3], set[set3].begin()),
    std::bind(copyOrIncreaseFrequency, std::ref(set[set3]), std::placeholders::_1));

}



void kartamyshev::list_popular(DictionarySet& set, std::istream& in, std::ostream& out)
{
  std::string name;
  int count;

  in >> name >> count;
  if (!in || count < 0)
  {
    throw std::logic_error("<INVALID ARGUMENT>");
  }
  if (set.count(name) == 0)
  {
    throw std::logic_error("<DICTIONARY DOES NOT EXIST>\n");
  }
  if (set.at(name).size() == 0)
  {
    throw std::logic_error("<DICTIONARY IS EMPTY>\n");
  }

  std::vector<std::pair<std::string, size_t>> word_counts(set.at(name).begin(), set.at(name).end());
  std::sort(word_counts.begin(), word_counts.end());
  std::reverse(word_counts.begin(), word_counts.end());
  if (set.at(name).size() > count)
  {
    auto end = std::next(word_counts.begin(), count);
    std::transform(word_counts.begin(), end, std::ostream_iterator< const std::string& >(std::cout, "\n"), getStr);
  }
  else
  {
  auto end = word_counts.end();
  std::transform(word_counts.begin(), word_counts.end(), std::ostream_iterator< const std::string& >(std::cout, "\n"), getStr);
  }

}
