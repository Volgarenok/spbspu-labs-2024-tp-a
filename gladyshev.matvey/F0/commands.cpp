#include "commands.hpp"

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

namespace gladyshev
{
  template< typename Function >
  void unionCmds(mainDic& dictionaries, std::istream& in, Function func)
   {
    dic result;
    std::string s = "";
    in >> s;
    std::string name1 = "";
    std::string name2 = "";
    in >> name1 >> name2;
    result = func(dictionaries.at(name1), dictionaries.at(name2));
    while (in)
    {
      if (in.get() == '\n')
      {
        break;
      }
      in >> name1;
      result = func(result, dictionaries.at(name1));
    }
    if (result.empty())
    {
      throw std::logic_error("RESULT OF OPERATION IS EMPTY");
    }
    dictionaries.insert(std::make_pair(s, result));
  }
}
void gladyshev::print_dictionary(const dic& dictionary, std::ostream& out)
{
  for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
  {
    out << " " << it->second << " " << it->first;
  }
  out << "\n";
}
void gladyshev::print_dictionaryL(const dic& dictionary, int n, std::ostream& out)
{
  for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
  {
    if (it->second > n)
    {
      out << " " << it->second << " " << it->first;
    }
  }
  out << "\n";
}
void gladyshev::addelem(mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  std::string key = "";
  size_t value = 0;
  in >> datasetName >> key >> value;
  auto it = dictionaries.find(datasetName);
  if (it == dictionaries.end())
  {
    throw std::logic_error("NO MATCHES");
  }
  it->second.insert(std::make_pair(key, value));
}
void gladyshev::save(const mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  std::string fileName = "";
  in >> datasetName >> fileName;
  std::ofstream outFile(fileName, std::ios::trunc);
  auto it = dictionaries.find(datasetName);
  outFile << datasetName;
  print_dictionary(it->second, outFile);
  outFile << "\n";
}
void gladyshev::intersect(mainDic& dictionaries, std::istream& in)
{
  unionCmds(dictionaries, in, intersectImpl);
}
void gladyshev::addition(mainDic& dictionaries, std::istream& in)
{
  unionCmds(dictionaries, in, additionImpl);
}
void gladyshev::complement(mainDic& dictionaries, std::istream& in)
{
  unionCmds(dictionaries, in, complementImpl);
}
bool gladyshev::inOther(const dic& dict1, const std::pair< std::string, int >& dict2)
{
  return dict1.find(dict2.first) != dict1.cend();
}
std::pair< std::string, int > gladyshev::updatePair(const std::pair< std::string, int >& d1pair, const dic& dict2)
{
  auto it = dict2.find(d1pair.first);
  return std::make_pair(d1pair.first, std::min(d1pair.second, it->second));
}
std::pair< std::string, int > gladyshev::updatePairPlus(const std::pair< std::string, int >& d1pair, const dic& dict2)
{
  auto it = dict2.find(d1pair.first);
  if (it != dict2.cend())
  {
    return std::make_pair(d1pair.first, d1pair.second + it->second);
  }
  return d1pair;
}
std::pair< std::string, int > gladyshev::updatePairMinus(const std::pair< std::string, int >& d1pair, const dic& dict2)
{
  auto it = dict2.find(d1pair.first);
  if (it != dict2.cend())
  {
    return std::make_pair(d1pair.first, d1pair.second - it->second);
  }
  return d1pair;
}
bool gladyshev::toErase(const std::pair< std::string, int >& pair)
{
  return pair.second > 0;
}
gladyshev::dic gladyshev::intersectImpl(const dic& dict1, const dic& dict2)
{
  dic result;
  dic temp;
  auto check = std::bind(inOther, std::cref(dict2), std::placeholders::_1);
  std::copy_if(dict1.begin(), dict1.end(), std::inserter(temp, temp.begin()), check);
  auto upair = std::bind(updatePair, std::placeholders::_1, std::cref(dict2));
  std::transform(temp.begin(), temp.end(), std::inserter(result, result.begin()), upair);
  return result;
}
void gladyshev::printInfo(std::ostream& out)
{
  out << "printdict <dataset> - display a dictionary with the corresponding name\n";
  out << "makedict <newdataset> <text> create a dictionary based on text from a file\n";
  out << "makedict <newdataset> <text> <number> create a dictionary based on text from a file with length number\n";
  out << "printgreater <dataset> <number> display all dictionary words that appear more than number times\n";
  out << "save <newdataset> <filename> save the dictionary to a file\n";
  out << "addelem <dataset> <key> <value> add an element to the specified dictionary\n";
  out << "delete <newdataset> delete dictionary with the corresponding name\n";
  out << "delete <newdataset> <key> delete an element with the corresponding key\n";
  out << "addition <newdataset> <dataset1> <dataset2> … <datasetn> combine an unlimited number of dictionaries\n";
  out << "intersect <newdataset> <dataset1> <dataset2> … <datasetn> intersect unlimited number of dictionaries\n";
  out << "complement <newdataset> <dataset1> <dataset2> … <datasetn> subtracts all dictionaries from the first one\n";
}
gladyshev::dic gladyshev::additionImpl(const dic& dict1, const dic& dict2)
{
  dic result;
  dic temp = dict1;
  auto upair = std::bind(updatePairPlus, std::placeholders::_1, std::cref(dict2));
  std::transform(temp.begin(), temp.end(), std::inserter(result, result.begin()), upair);
  auto check = std::bind(inOther, std::cref(dict2), std::placeholders::_1);
  std::copy_if(dict2.begin(), dict2.end(), std::inserter(result, result.begin()), check);
  return result;
}
gladyshev::dic gladyshev::complementImpl(const dic& dict1, const dic& dict2)
{
  dic result;
  dic temp = dict1;
  auto upair = std::bind(updatePairMinus, std::placeholders::_1, std::cref(dict2));
  std::transform(temp.begin(), temp.end(), std::inserter(result, result.begin()), upair);
  dic finres;
  std::copy_if(result.begin(), result.end(), std::inserter(finres, finres.begin()), toErase);
  return finres;
}
void gladyshev::deleteDict(mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  in >> datasetName;
  auto it = dictionaries.find(datasetName);
  if (it == dictionaries.end())
  {
    throw std::logic_error("NO MATCHES");
  }
  dictionaries.erase(datasetName);
}
void gladyshev::deleteName(mainDic& dictionaries, std::istream& in)
{
  std::string datasetName = "";
  std::string name = "";
  in >> datasetName >> name;
  auto it = dictionaries.find(datasetName);
  if (it == dictionaries.end())
  {
    throw std::logic_error("NO MATCHES");
  }
  it->second.erase(name);
}
void gladyshev::print_dictionaries(const mainDic& dictionaries, std::istream& in, std::ostream& out)
{
  std::string s = "";
  in >> s;
  auto it = dictionaries.find(s);
  if (it != dictionaries.end())
  {
    if (it->second.empty())
    {
      throw std::overflow_error("<EMPTY>");
    }
    out << it->first;
    print_dictionary(it->second, out);
  }
}
void gladyshev::print_dictionariesL(const mainDic& dictionaries, std::istream& in, std::ostream& out)
{
  size_t n = 0;
  std::string s = "";
  in >> s >> n;
  auto it = dictionaries.find(s);
  if (it != dictionaries.end())
  {
    if (it->second.empty())
    {
      throw std::overflow_error("<NO MATCHES>");
    }
    out << it->first;
    print_dictionaryL(it->second, n, out);
  }
}
