#include "commands.hpp"
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>

void change(std::istream& in, piyavkin::Dictionary& dic)
{
  size_t val = 0;
  std::string key = "";
  in >> key >> val;
  if (in)
  {
    auto dicIt = dic.dic.find(key);
    if (dicIt != dic.dic.end())
    {
      dic.dic.erase(key);
    }
    dic.dic.insert(std::pair< std::string, size_t >(key, val));
  }
}

std::pair< piyavkin::iterator, bool > add(std::istream& in, piyavkin::dic_t& dicts)
{
  std::string name = "";
  in >> name;
  return dicts.insert(std::make_pair(name, piyavkin::Dictionary()));
}

void piyavkin::input(std::istream& in, dic_t& dicts)
{
  iterator it = add(in, dicts).first;
  Dictionary d;
  in >> d;
  it->second = d;
}

void piyavkin::print(std::istream& in, const dic_t& dicts)
{
  std::string nameDict = "";
  std::string nameFile = "";
  in >> nameDict >> nameFile;
  std::ifstream file(nameFile);
  if (!file.is_open())
  {
    throw std::out_of_range("");
  }
  std::ofstream out(nameFile);
  dic_t::const_iterator it = dicts.find(nameDict);
  if (it != dicts.cend())
  {
    out << it->first << "\n";
    out << it->second;
  }
  else
  {
    throw std::out_of_range("");
  }
}

bool greaterSec(const std::pair< std::string, size_t >& a, const std::pair< std::string, size_t >& b)
{
  return a.second > b.second;
}

void output(std::ostream& out, const std::vector< std::pair< std::string, size_t > >& v, size_t n)
{
  using out_it_t = std::ostream_iterator< piyavkin::Node >;
  std::transform(v.cbegin(), v.cbegin() + n, out_it_t{out, "\n"}, piyavkin::getVal);
}

void piyavkin::topFreq(std::istream& in, std::ostream& out, const dic_t& dicts)
{
  std::string nameDic = "";
  size_t n = 0;
  in >> nameDic >> n;
  auto it = dicts.find(nameDic);
  const Dictionary dic = it->second;
  if (n > dic.dic.size())
  {
    throw std::out_of_range("");
  }
  std::vector< std::pair< std::string, size_t > > res(dic.dic.cbegin(), dic.dic.cend());
  std::sort(res.begin(), res.end(), greaterSec);
  output(out, res, n);
}

piyavkin::iterator piyavkin::addDict(std::istream& in, dic_t& dicts)
{
  auto pair = add(in, dicts);
  if (!pair.second)
  {
    throw std::out_of_range("");
  }
  return pair.first;
}

piyavkin::iterator piyavkin::cmdChange(std::istream& in, dic_t& dicts)
{
  std::string name = "";
  in >> name;
  iterator it = dicts.find(name);
  if (it == dicts.end())
  {
    throw std::out_of_range("");
  }
  change(in, it->second);
  return it;
}

piyavkin::iterator piyavkin::makeDict(std::istream& in, dic_t& dicts)
{
  iterator it = add(in, dicts).first;
  it->second.dic.clear();
  std::string nameFile = "";
  in >> nameFile;
  std::ifstream file(nameFile);
  Dictionary d;
  file >> d;
  it->second = d;
  return it;
}

bool isLoc(const std::pair< std::string, size_t >& p, const std::map< std::string, size_t >& tree)
{
  return tree.find(p.first) != tree.cend();
}

std::pair< std::string, size_t > inter(const std::pair< std::string, size_t >& p1, const std::pair< std::string, size_t >& p2)
{
  return std::pair< std::string, size_t >(p1.first, std::min(p1.second, p2.second));
}

bool less(const std::pair< std::string, size_t >& p1, const std::pair< std::string, size_t >& p2)
{
  return p1.first < p2.first;
}

piyavkin::iterator piyavkin::intersect(std::istream& in, dic_t& dicts)
{
  std::string newDic = "";
  std::string lhs = "";
  std::string rhs = "";
  in >> newDic >> lhs >> rhs;
  std::map< std::string, size_t > rhsTree = dicts.at(rhs).dic;
  std::map< std::string, size_t > lhsTree = dicts.at(lhs).dic;
  std::map< std::string, size_t > newTree;
  std::set_intersection(lhsTree.begin(), lhsTree.end(), rhsTree.begin(), rhsTree.end(), std::inserter(newTree, newTree.end()), less);
  std::vector< std::pair< std::string, size_t > > v(newTree.size(), {"", 0});
  std::copy_if(rhsTree.cbegin(), rhsTree.cend(), v.begin(), std::bind(isLoc, std::placeholders::_1, newTree));
  std::map< std::string, size_t > temp;
  std::transform(newTree.begin(), newTree.end(), v.cbegin(), std::inserter(temp, temp.end()), inter);
  Dictionary res;
  res.dic = temp;
  if (dicts.find(newDic) != dicts.end())
  {
    dicts.erase(newDic);
  }
  return dicts.insert(std::pair< std::string, Dictionary >(newDic, res)).first;
}

std::pair< std::string, size_t > unionF(const std::pair< std::string, size_t >& p1, const std::pair< std::string, size_t >& p2)
{
  return std::pair< std::string, size_t >(p1.first, std::max(p1.second, p2.second));
}

piyavkin::iterator unionImpl(piyavkin::dic_t& dicts, const std::string& newDic, const std::string& lhs, const std::string& rhs)
{
  using namespace piyavkin;
  const std::map< std::string, size_t > rhsTree = dicts.at(rhs).dic;
  const std::map< std::string, size_t > lhsTree = dicts.at(lhs).dic;
  std::map< std::string, size_t > newTree;
  std::set_union(lhsTree.begin(), lhsTree.end(), rhsTree.begin(), rhsTree.end(), std::inserter(newTree, newTree.end()), less);
  std::vector< std::pair< std::string, size_t > > v(newTree.size(), {"", 0});
  std::copy_if(rhsTree.cbegin(), rhsTree.cend(), v.begin(), std::bind(isLoc, std::placeholders::_1, newTree));
  std::map< std::string, size_t > temp;
  std::transform(newTree.begin(), newTree.end(), v.cbegin(), std::inserter(temp, temp.end()), unionF);
  Dictionary res;
  res.dic = temp;
  if (dicts.find(newDic) != dicts.end())
  {
    dicts.erase(newDic);
  }
  return dicts.insert(std::pair< std::string, Dictionary >(newDic, res)).first;
}

piyavkin::iterator piyavkin::unionD(std::istream& in, dic_t& dicts)
{
  std::string newDic = "";
  std::string lhs = "";
  std::string rhs = "";
  in >> newDic >> lhs >> rhs;
  return unionImpl(dicts, newDic, lhs, rhs);
}

bool isUnloc(const std::pair< std::string, size_t >& p, const std::map< std::string, size_t >& tree)
{
  return !isLoc(p, tree);
}

piyavkin::iterator piyavkin::uniqueD(std::istream& in, dic_t& dicts)
{
  std::string newDic = "";
  std::string lhs = "";
  std::string rhs = "";
  in >> newDic >> lhs >> rhs;
  std::map< std::string, size_t > rhsTree = dicts.at(rhs).dic;
  std::map< std::string, size_t > lhsTree = dicts.at(lhs).dic;
  std::map< std::string, size_t > newTree;
  std::set_intersection(rhsTree.begin(), rhsTree.end(), lhsTree.begin(), lhsTree.end(), std::inserter(newTree, newTree.end()), less);
  std::map< std::string, size_t > temp;
  std::copy_if(lhsTree.cbegin(), lhsTree.cend(), std::inserter(temp, temp.end()), std::bind(isUnloc, std::placeholders::_1, newTree));
  Dictionary res;
  res.dic = temp;
  if (dicts.find(newDic) != dicts.end())
  {
    dicts.erase(newDic);
  }
  return dicts.insert(std::pair< std::string, Dictionary >(newDic, res)).first;
}

piyavkin::iterator piyavkin::addDtoD(std::istream& in, dic_t& dicts)
{
  std::string lhs = "";
  std::string rhs = "";
  in >> lhs >> rhs;
  return unionImpl(dicts, lhs, lhs, rhs);
}

std::pair< std::string, size_t > minus(const std::pair< std::string, size_t >& p, std::map< std::string, size_t >& t)
{
  auto it = t.find(p.first);
  if (it != t.end() && it->second < p.second)
  {
    t.erase(it);
    return {"", 0};
  }
  else
  {
    if (it == t.end())
    {
      return {"", 0};
    }
    it->second -= p.second;
  }
  return *it;
}

bool isNotZero(const std::pair< std::string, size_t >& p)
{
  return p.second != 0;
}

piyavkin::iterator piyavkin::subD(std::istream& in, dic_t& dicts)
{
  std::string lhs = "";
  std::string rhs = "";
  in >> lhs >> rhs;
  std::map< std::string, size_t > rhsTree = dicts.at(rhs).dic;
  std::map< std::string, size_t > lhsTree = dicts.find(lhs)->second.dic;
  std::map< std::string, size_t > newTree;
  std::set_intersection(rhsTree.begin(), rhsTree.end(), lhsTree.begin(), lhsTree.end(), std::inserter(newTree, newTree.end()), less);
  std::vector< std::pair< std::string, size_t > > v(lhsTree.size(), { "", 0 });
  std::copy_if(rhsTree.cbegin(), rhsTree.cend(), v.begin(), std::bind(isLoc, std::placeholders::_1, newTree));
  std::map< std::string, size_t > temp;
  std::transform(v.cbegin(), v.cend(), std::inserter(temp, temp.end()), std::bind(minus, std::placeholders::_1, lhsTree));
  std::map< std::string, size_t > temp2;
  std::copy_if(temp.begin(), temp.end(), std::inserter(temp2, temp2.end()), isNotZero);
  Dictionary res;
  res.dic = temp2;
  dicts.erase(lhs);
  return dicts.insert(std::pair< std::string, Dictionary >(lhs, res)).first;
}
