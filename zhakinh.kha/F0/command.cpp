#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>

#include "command.hpp"

void change(std::istream& in, zhakha::Dictionary& dic)
{
  size_t val = 0;
  std::string key = "";
  in >> key >> val;
  if (in)
  {
    dic.dic[key] = val;
  }
}

std::pair<zhakha::DictionaryIterator, bool> add(std::istream& in, zhakha::DictionaryMap& dicts)
{
  std::string name = "";
  in >> name;
  if (in) {
    return dicts.insert(std::make_pair(name, zhakha::Dictionary()));
  }
  throw std::invalid_argument("Invalid input.");
}

void zhakha::input(std::istream& in, DictionaryMap& dicts)
{
  DictionaryIterator it = add(in, dicts).first;
  Dictionary d;
  in >> d;
  it->second = d;
}

void zhakha::print(std::istream& in, const DictionaryMap& dicts)
{
  std::string nameDict = "", nameFile = "";
  in >> nameDict >> nameFile;

  auto it = dicts.find(nameDict);
  if (it == dicts.end())
  {
    throw std::out_of_range("Dictionary not found.");
  }

  std::ofstream out(nameFile);
  if (!out)
  {
    throw std::ios_base::failure("Failed to open output file.");
  }

  out << it->first << "\n" << it->second;
}

bool greaterSec(const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b)
{
  return a.second > b.second;
}

void outputTopN(std::ostream& out, const std::vector<std::pair<std::string, size_t>>& v, size_t n)
{
  for (size_t i = 0; i < n && i < v.size(); ++i)
  {
    out << v[i].first << ": " << v[i].second << "\n";
  }
}

void zhakha::topFreq(std::istream& in, std::ostream& out, const DictionaryMap& dicts)
{
  std::string nameDic = "";
  size_t n = 0;
  in >> nameDic >> n;

  auto it = dicts.find(nameDic);
  if (it == dicts.end())
  {
    throw std::out_of_range("Dictionary not found.");
  }

  const Dictionary& dic = it->second;
  if (n > dic.dic.size())
  {
    throw std::out_of_range("Requested number of top frequencies exceeds dictionary size.");
  }

  std::vector<std::pair<std::string, size_t>> res(dic.dic.begin(), dic.dic.end());
  std::sort(res.begin(), res.end(), greaterSec);
  outputTopN(out, res, n);
}

zhakha::DictionaryIterator zhakha::addDict(std::istream& in, DictionaryMap& dicts)
{
  auto pair = add(in, dicts);
  if (!pair.second)
  {
    throw std::out_of_range("Dictionary already exists.");
  }
  return pair.first;
}

zhakha::DictionaryIterator zhakha::cmdChange(std::istream& in, DictionaryMap& dicts)
{
  std::string name = "";
  in >> name;
  auto it = dicts.find(name);
  if (it == dicts.end())
  {
    throw std::out_of_range("Dictionary not found.");
  }
  size_t val = 0;
  std::string key = "";
  in >> key >> val;
  if (in)
  {
    it->second.dic[key] = val;
  }
  return it;
}

zhakha::DictionaryIterator zhakha::makeDict(std::istream& in, DictionaryMap& dicts)
{
  auto it = addDict(in, dicts);
  it->second.dic.clear();

  std::string nameFile = "";
  in >> nameFile;

  std::ifstream file(nameFile);
  if (!file)
  {
    throw std::ios_base::failure("Failed to open input file.");
  }

  Dictionary d;
  file >> d;
  it->second = d;
  return it;
}

zhakha::DictionaryIterator zhakha::intersect(std::istream& in, DictionaryMap& dicts)
{
  std::string newDic, lhs, rhs;
  in >> newDic >> lhs >> rhs;

  const auto& lhsTree = dicts.at(lhs).dic;
  const auto& rhsTree = dicts.at(rhs).dic;
  std::map<std::string, size_t> newTree;

  std::set_intersection(lhsTree.begin(), lhsTree.end(), rhsTree.begin(), rhsTree.end(),
    std::inserter(newTree, newTree.end()), [](const auto& p1, const auto& p2)
    {
      return p1.first < p2.first;
    });

  Dictionary res;
  res.dic = std::move(newTree);
  return dicts.insert_or_assign(newDic, std::move(res)).first;
}

zhakha::DictionaryIterator zhakha::unionD(std::istream& in, DictionaryMap& dicts)
{
  std::string newDic, lhs, rhs;
  in >> newDic >> lhs >> rhs;

  const auto& lhsTree = dicts.at(lhs).dic;
  const auto& rhsTree = dicts.at(rhs).dic;
  std::map<std::string, size_t> newTree;

  std::set_union(lhsTree.begin(), lhsTree.end(), rhsTree.begin(), rhsTree.end(),
    std::inserter(newTree, newTree.end()), [](const auto& p1, const auto& p2)
    {
      return p1.first < p2.first;
    });

  Dictionary res;
  res.dic = std::move(newTree);
  return dicts.insert_or_assign(newDic, std::move(res)).first;
}

zhakha::DictionaryIterator zhakha::uniqueD(std::istream& in, DictionaryMap& dicts)
{
  std::string newDic, lhs, rhs;
  in >> newDic >> lhs >> rhs;

  const auto& lhsTree = dicts.at(lhs).dic;
  const auto& rhsTree = dicts.at(rhs).dic;
  std::map<std::string, size_t> newTree;

  std::set_difference(lhsTree.begin(), lhsTree.end(), rhsTree.begin(), rhsTree.end(),
    std::inserter(newTree, newTree.end()), [](const auto& p1, const auto& p2)
    {
      return p1.first < p2.first;
    });

  Dictionary res;
  res.dic = std::move(newTree);
  return dicts.insert_or_assign(newDic, std::move(res)).first;
}

zhakha::DictionaryIterator zhakha::addDtoD(std::istream& in, DictionaryMap& dicts)
{
  std::string target, source;
  in >> target >> source;

  auto& targetTree = dicts.at(target).dic;
  const auto& sourceTree = dicts.at(source).dic;

  for (auto it = sourceTree.begin(); it != sourceTree.end(); ++it)
  {
    const std::string& key = it->first;
    size_t value = it->second;
    targetTree[key] += value;
  }

  return dicts.find(target);
}

zhakha::DictionaryIterator zhakha::subD(std::istream& in, DictionaryMap& dicts)
{
  std::string target, source;
  in >> target >> source;

  auto& targetTree = dicts.at(target).dic;
  const auto& sourceTree = dicts.at(source).dic;

  for (auto it = sourceTree.begin(); it != sourceTree.end(); ++it)
  {
    const std::string& key = it->first;
    size_t value = it->second;
    auto targetIt = targetTree.find(key);
    if (targetIt != targetTree.end())
    {
      if (targetIt->second < value)
      {
        targetIt->second = 0;
      }
      else
      {
        targetIt->second -= value;
      }
      if (targetIt->second == 0)
      {
        targetTree.erase(targetIt);
      }
    }
  }

  return dicts.find(target);
}
