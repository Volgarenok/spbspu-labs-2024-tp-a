#include "commands.hpp"
#include <fstream>
#include <random>
#include <set>
#include "dictionary.hpp"

using val_t = std::pair< std::string, std::set< std::string > >;

void novokhatskiy::unique(dictionaries& dict, std::istream& in)
{
  std::string newName = {};
  std::string nameOfDict1 = {};
  std::string nameOfDict2 = {};
  in >> newName >> nameOfDict1 >> nameOfDict2;
  auto dict1 = dict.at(nameOfDict1);
  auto dict2 = dict.at(nameOfDict2);
  auto res = dict1;
  for (auto i = dict1.getDict().cbegin(); i != dict1.getDict().cend(); i++)
  {
    for (auto j = dict2.getDict().cbegin(); j != dict2.getDict().cend(); j++)
    {
      if (*i == *j)
      {
        continue;
      }
      res.getDict().insert(*j);
    }
  }
  dict.insert({ newName, res });
}


void novokhatskiy::search(dictionaries& dict, std::istream& in)
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

//void novokhatskiy::editExample(dictionaries& dict, std::istream& in)
//{
//  std::string nameOfDict = {};
//  std::string word = {};
//  std::string example = {};
//  std::string newExample = {};
//  in >> nameOfDict >> word >> example >> newExample;
//  auto tmp = dict.find(nameOfDict);
//  val_t& type = tmp->second.getValue(word);
//  auto rs = type.second.find(example);
//}

 

void novokhatskiy::merge(dictionaries& dict, std::istream& in)
{
  std::string newName = {};
  std::string nameOfDict1 = {};
  std::string nameOfDict2 = {};
  in >> newName >> nameOfDict1 >> nameOfDict2;
  auto dict1 = dict.at(nameOfDict1);
  auto dict2 = dict.at(nameOfDict2);
  auto res = dict1;
  for (auto i = dict2.getDict().cbegin(); i != dict2.getDict().cend(); i++)
  {
    res.getDict().insert(*i);
  }
  dict.insert({ newName, res });
}

void novokhatskiy::editTranslation(dictionaries& dict, std::istream& in, std::ostream& out)
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
  val_t& tmp = (*it).second.getValue(word);
  tmp.first = trans;
}

void novokhatskiy::printHelp()
{
  std::cout << "Commands:\n";
  std::cout << "1) find - < word >\n";
  std::cout << "2) insert - < dict name > < word > < translation > < example >\n";
  std::cout << "3) delete - < word >\n";
  std::cout << "4) merge - < dict name > < dict name >\n";
  std::cout << "5) save - < dict name > < output >\n";
  std::cout << "6) unique - < dict name > < dict name >\n";
  std::cout << "7) print - < dict name >\n";
  std::cout << "8) random - < count > < dict name > < dict name >\n";
  std::cout << "9) search - < dict name > < word > < word >\n";
  std::cout << "10) edit - < word > < new translation >\n";
}

template< class T >
T randomNumber(T min, T max)
{
  std::random_device random;
  std::mt19937 num(random());
  std::uniform_real_distribution< float > dist(min, max);
  return static_cast< T >(dist(num));
}

//void novokhatskiy::random(dictionaries& dict, std::istream& in, std::ostream& out)
//{
//  std::string nameOfNewDict;
//  std::string nameOfDict1;
//  std::string nameOfDict2;
//  size_t count = {1};
//  out << "Input a name of a new dictionary:\n";
//  //in >> nameOfNewDict;
//  out << "Input the size of a new dictionary:\n";
//  //in >> count;
//  if (count <= 0)
//  {
//    throw std::logic_error("Count can't be zero or negative");
//  }
//  out << "Input a name of the first dictionary:\n";
//  //in >> nameOfDict1;
//  out << "Input a name of the second dictionary:\n";
//  //in >> nameOfDict2;
//  auto dict1 = dict.find("dict1");//nameOfDict1
//  auto dict2 = dict.find("dict2");//nameOfDict2
//
//  if (dict1->second.size() + dict2->second.size() < count)
//  {
//    throw std::logic_error("Not enough keys");
//  }
//  Dictionary tmp;
//  if (count % 2 == 1)
//  {
//    for (size_t i = 0; i < (count / 2); i++)
//    {
//      size_t dist = randomNumber(0ull, dict1->second.size());
//      auto it1 = dict1->second.getDict().cbegin();
//      std::advance(it1, dist);
//      tmp.getDict().insert(*it1);
//    }
//    for (size_t i = 0; i < (count / 2) + 1; i++)
//    {
//      size_t dist = randomNumber(0ull, dict2->second.size());
//      auto it2 = dict2->second.getDict().cbegin();
//      /*std::advance(it2, dist);
//      tmp.getDict().insert(*it2);*/
//    }
//  }
//  else
//  {
//    for (size_t i = 0; i < count / 2; i++)
//    {
//      size_t dist = randomNumber(0ull, dict1->second.size());
//      auto it1 = dict1->second.getDict().cbegin();
//      std::advance(it1, dist);
//      tmp.getDict().insert(*it1);
//    }
//    for (size_t i = 0; i < count / 2; i++)
//    {
//      size_t dist = randomNumber(0ull, dict2->second.size());
//      auto it2 = dict2->second.getDict().cbegin();
//      std::advance(it2, dist);
//      tmp.getDict().insert(*it2);
//    }
//  }
//  dict["dict3"] = tmp;
//}

void novokhatskiy::find(const dictionaries& dict, std::istream& in, std::ostream& out)
{
  if (dict.empty())
  {
    throw std::logic_error("Empty dict");
  }
  std::string nameOfDict;
  std::string word;
  out << "Input a name of the dictionary:\n";
  in >> nameOfDict;
  out << "Input a word:\n";
  in >> word;
  const Dictionary& tmp = dict.at(nameOfDict);
  tmp.find(word, out);
}

void novokhatskiy::deleteWord(dictionaries& dict, std::istream& in)
{
  std::string nameOfDict;
  std::string word;
  in >> nameOfDict >> word;
  dict.at(nameOfDict).remove(word);
}
void novokhatskiy::save(const dictionaries& dict, std::istream& in, std::ostream& out)
{
  std::string nameOfDict;
  std::string nameOfFile;
  out << "Input a name of the dictionary:\n";
  in >> nameOfDict;
  out << "Input filename:\n";
  in >> nameOfFile;
  std::ofstream file(nameOfFile);
  const Dictionary& tmp = dict.at(nameOfDict);
  file << nameOfDict << ' ' << tmp;
}

void novokhatskiy::insert(dictionaries& dict, std::istream& in)
{
  std::string nameOfDict;
  Dictionary tmp;
  in >> nameOfDict >> tmp;
  dict[nameOfDict] = tmp;
  tmp = {};
  while (!in.eof())
  {
    in >> nameOfDict >> tmp;
    dict.at(nameOfDict).addValue(std::move(tmp));
  }
  in.clear();
}

void novokhatskiy::print(const dictionaries& dict, std::istream& in, std::ostream& out)
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
