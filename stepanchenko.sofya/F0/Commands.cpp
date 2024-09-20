#include "Commands.hpp"

#include <iostream>
#include "Commands.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fstream>

#include "Utility.hpp"

struct isName
{
  bool operator()(const stepanchenko::CrossRefs & cross_refs, const std::string& name)
  {
    return cross_refs.getName() == name;
  }
};

struct hasWord
{
  bool operator()(std::pair< size_t, std::string >& line, std::list< size_t > & wordList)
  {
    return std::find(wordList.begin(), wordList.end(), line.first) != wordList.end();
    }
};

template < typename Iter1, typename Iter2 >
struct Swap
{
  Iter1 iter1;
  Iter2 iter2;
  void operator()(Iter1 i1, Iter2 i2);
};

void stepanchenko::create_tableCmd(std::vector< CrossRefs > cross_refs, std::istream& in)
{
  std::string tableName, file;
  in >> tableName >> file;
  using namespace std::placeholders;
  auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), _1, tableName));
  if (iter == cross_refs.end())
  {
    iter->createTable(tableName, file);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND");
  }
}

void stepanchenko::print_linesCmd(std::vector< CrossRefs > cross_refs, std::istream& in, std::ostream& out)
{
  std::string word, tName;
  in >> word >> tName;
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord = iterTable->search(word);
  std::vector< std::pair< size_t, std::string > > lines = iterTable->getLines();
  std::vector< std::pair< size_t, std::string > > t_lines;
  std::copy_if(lines.begin(), lines.end(), std::back_inserter(t_lines), std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  std::for_each(t_lines.begin(), t_lines.end(), [&](const std::pair<size_t, std::string>& line) {
    printL(line, out);
  });
}

void stepanchenko::delete_lines(std::vector< CrossRefs > cross_refs, std::istream& in)
{
  std::string word, tName, fName;
  in >> word >> tName >> fName;
  checkName(cross_refs, tName);
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord = iterTable->search(word);
  auto iter = std::remove_if(iterTable->lines_.begin(), iterTable->lines_.end(), std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  iterTable->lines_.erase(iter, iterTable->lines_.end());
  iterTable->removeEntry(iterWord->first);
}

void stepanchenko::move_lines_downCmd(std::vector< CrossRefs > cross_refs, std::istream& in)
{
  std::string word, tName, fName;
  in >> word >> tName >> fName;
  checkName(cross_refs, tName);
  std::ofstream file;
  file.open(fName);
  if (!file.is_open())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord = iterTable->search(word);
  std::vector< std::pair< size_t, std::string > > t_lines;
  std::copy_if(iterTable->lines_.begin(), iterTable->lines_.end(), std::back_inserter(t_lines), std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  auto iter = std::remove_if(iterTable->lines_.begin(), iterTable->lines_.end(), std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  iterTable->lines_.erase(iter, iterTable->lines_.end());

  std::move(iterTable->lines_.begin(), iterTable->lines_.end(), std::back_inserter(t_lines));
  iterTable->lines_ = t_lines;
  writeToFile(iterTable->lines_, file);
  file.close();
}

void stepanchenko::get_selectionCmd(std::vector< CrossRefs > cross_refs, std::istream& in)
{
  std::string word1, word2, tName, fName, rName;
  in >> word1 >> word2 >> tName >> fName >> rName;
  checkName(cross_refs, tName);
  std::ofstream file;
  file.open(rName);
  if (!file.is_open())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord1 = iterTable->search(word1);
  auto iterWord2 = iterTable->search(word2);
  std::list< size_t > list;
  std::merge(iterWord1->second.begin(), iterWord1->second.end(),
    iterWord2->second.begin(), iterWord2->second.end(),
    std::back_inserter(list)
  );
  std::vector< std::pair< size_t, std::string > > t_lines;
  std::copy_if(
    iterTable->lines_.begin(), iterTable->lines_.end(),
    std::back_inserter(t_lines),
    std::bind(hasWord(), std::placeholders::_1, list)
  );
  writeToFile(t_lines, file);
}
