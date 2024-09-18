#include "commands.hpp"
#include <fstream>
#include <algorithm>
#include <set>
#include "dictionary.hpp"

using val_t = std::pair<std::string, std::set<std::string>>;

void novokhatskiy::unique(dictionaries &dict, std::istream &in)
{
  std::string newName = {};
  std::string nameOfDict1 = {};
  std::string nameOfDict2 = {};
  in >> newName >> nameOfDict1 >> nameOfDict2;
  auto dict1 = dict.at(nameOfDict1);
  auto dict2 = dict.at(nameOfDict2);
  Dictionary res;
  auto begin1 = dict1.getDict().cbegin();
  auto end1 = dict1.getDict().cend();
  auto begin2 = dict2.getDict().cbegin();
  auto end2 = dict2.getDict().cend();
  std::set_difference(begin1, end1, begin2, end2, std::inserter(res.getDict(), res.getDict().begin()));
  dict.insert({ newName, res });
}

void novokhatskiy::search(dictionaries &dict, std::istream &in)
{
  std::string newDict = {};
  std::string nameOfDict1 = {};
  std::string nameOfDict2 = {};
  std::string line1 = {};
  std::string line2 = {};
  in >> newDict >> nameOfDict1 >> nameOfDict2 >> line1 >> line2;
  if (line1 == "" || line2 == "")
  {
    throw std::logic_error("The range can't be empty");
  }
  auto dict1 = dict.at(nameOfDict1);
  auto begin1 = dict1.getDict().cbegin();
  Dictionary res;
  while (begin1 != dict1.getDict().cend() && begin1->first != line2)
  {
    res.getDict().insert(*begin1++);
  }
  auto dict2 = dict.at(nameOfDict2);
  auto begin2 = dict2.getDict().cbegin();
  while (begin2 != dict2.getDict().cend() && begin2->first != line2)
  {
    res.getDict().insert(*begin2++);
  }
  dict[newDict] = res;
}

void novokhatskiy::merge(dictionaries &dict, std::istream &in)
{
  std::string newName = {};
  std::string nameOfDict1 = {};
  std::string nameOfDict2 = {};
  in >> newName >> nameOfDict1 >> nameOfDict2;
  auto dict1 = dict.at(nameOfDict1);
  auto dict2 = dict.at(nameOfDict2);
  auto res = dict1;
  std::copy(dict2.getDict().cbegin(), dict2.getDict().cend(), std::inserter(res.getDict(), res.getDict().end()));
  dict.insert({newName, res});
}

void novokhatskiy::editTranslation(dictionaries &dict, std::istream &in)
{
  std::string dictName = {};
  std::string word = {};
  std::string trans = {};
  in >> dictName >> word >> trans;
  auto it = dict.find(dictName);
  if (it == dict.cend())
  {
    throw std::logic_error("Dict doesn't exist");
  }
  val_t &tmp = (*it).second.getValue(word);
  tmp.first = trans;
}

void novokhatskiy::printHelp()
{
  std::cout << "Commands:\n";
  std::cout << "1) find - < dict name > < word >\n";
  std::cout << "2) insert - < dict name > < word > < translation > < example >\n";
  std::cout << "3) delete - <dict name > < word >\n";
  std::cout << "4) merge - < result dict > < dict name > < dict name >\n";
  std::cout << "5) save - < dict name > < name of file >\n";
  std::cout << "6) unique - < result dict > < dict name > < dict name >\n";
  std::cout << "7) print - < dict name >\n";
  std::cout << "8) random - < result dict > < count > < dict name > < dict name >\n";
  std::cout << "9) search - < result dict > < the first dict > < the second dict > < word > < word >\n";
  std::cout << "10) edit - < dict name > < word > < new translation >\n";
}

void novokhatskiy::randomDict(dictionaries &dict, std::istream &in, std::random_device &randomDevice)
{
  std::string nameOfNewDict;
  std::string nameOfDict1;
  std::string nameOfDict2;
  size_t count = {};
  in >> nameOfNewDict >> count >> nameOfDict1 >> nameOfDict2;
  if (count <= 0)
  {
    throw std::logic_error("Count can't be zero or negative");
  }
  auto dict1 = dict.at(nameOfDict1);
  auto dict2 = dict.at(nameOfDict2);

  if (dict1.size() + dict2.size() < count)
  {
    throw std::logic_error("Not enough keys");
  }
  std::uniform_int_distribution< size_t > dist1(0, (dict1.size()));
  Dictionary tmp;
  for (size_t i = 0; i < count - (count / 2); i++)
  {
    size_t dist = dist1(randomDevice);
    auto it1 = dict1.getDict().cbegin();
    std::advance(it1, dist);
    tmp.getDict().insert(*it1);
  }
  std::uniform_int_distribution< size_t > dist2(0, dict2.size());
  for (size_t i = 0; i < count / 2; i++)
  {
    size_t dist = dist2(randomDevice);
    auto it2 = dict2.getDict().cbegin();
    std::advance(it2, dist);
    tmp.getDict().insert(*it2);
  }
  dict[nameOfNewDict] = tmp;
}

void novokhatskiy::find(const dictionaries &dict, std::istream &in, std::ostream &out)
{
  if (dict.empty())
  {
    throw std::logic_error("Empty dict");
  }
  std::string nameOfDict;
  std::string word;
  in >> nameOfDict >> word;
  const Dictionary &tmp = dict.at(nameOfDict);
  tmp.find(word, out);
}

void novokhatskiy::deleteWord(dictionaries &dict, std::istream &in)
{
  std::string nameOfDict;
  std::string word;
  in >> nameOfDict >> word;
  dict.at(nameOfDict).remove(word);
}
void novokhatskiy::save(const dictionaries &dict, std::istream &in)
{
  std::string nameOfDict;
  std::string nameOfFile;
  in >> nameOfDict >> nameOfFile;
  std::ofstream file(nameOfFile);
  const Dictionary &tmp = dict.at(nameOfDict);
  file << nameOfDict << ' ' << tmp;
}

void novokhatskiy::insert(dictionaries &dict, std::istream &in)
{
  std::string nameOfDict;
  Dictionary tmp;
  in >> nameOfDict >> tmp;
  dict[nameOfDict] = tmp;
  tmp = {};
  while (!in.eof())
  {
    in >> nameOfDict >> tmp;
    if (dict.find(nameOfDict) == dict.cend())
    {
      dict[nameOfDict] = tmp;
    }
    dict.at(nameOfDict).addValue(std::move(tmp));
    tmp = {};
    nameOfDict = "";
  }
  in.clear();
}

void novokhatskiy::print(const dictionaries &dict, std::istream &in, std::ostream &out)
{
  if (dict.empty())
  {
    throw std::logic_error("Empty dictionary");
  }
  std::string nameOfDict;
  in >> nameOfDict;
  auto tmp = dict.find(nameOfDict);
  out << tmp->second;
}
