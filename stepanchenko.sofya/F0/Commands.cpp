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
  bool operator()(stepanchenko::CrossRefs & cross_ref, const std::string& name)
  {
    return cross_ref.getName() == name;
  }
};

struct hasWord
{
  bool operator()(std::pair< size_t, std::string >& line, std::list< size_t > & wordList)
  {
    return std::find(wordList.begin(), wordList.end(), line.first) != wordList.end();
  }
};

void stepanchenko::create_tableCmd(std::vector< CrossRefs >& cross_refs, std::istream& in)
{
  std::string tableName, file;
  in >> tableName >> file;
  using namespace std::placeholders;
  auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), _1, tableName));
  if (iter == cross_refs.end())
  {
    CrossRefs cr;
    cr.createTable(tableName, file);
    cross_refs.push_back(cr);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void stepanchenko::add_to_tableCmd(std::vector< CrossRefs >& cross_refs, std::istream& in)
{
  std::string tableName, fName;
  checkName(cross_refs, tableName);
  auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, tableName));
  iter->append(fName);
}

void stepanchenko::get_intersectionCmd(std::vector< CrossRefs >& cross_refs, std::istream& in)
{
  std::string intersectionTable, table1, table2;
  in >> intersectionTable >> table1 >> table2;
  checkName(cross_refs, intersectionTable);
  auto first_map = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, table1));
  auto second_map = std::find_if(cross_refs.begin(), cross_refs.end(), std::bind(isName(), std::placeholders::_1, table2));

  CrossRefs intersected;
  auto min_max = std::minmax_element(first_map, second_map);

  for (auto it = min_max.first->begin(); it != min_max.first->end(); ++it)
  {
    if (isInIntersection(*it, std::ref(*min_max.second)))
    {
      intersected.insert(*it);
      auto iter = min_max.second->search(it->first);
      auto line = std::find_if(min_max.second->lines_.begin(), min_max.second->lines_.begin(),
      std::bind(hasWord(), std::placeholders::_1, iter->second));
      intersected.extend(iter->first, *line);
    }
  }
  cross_refs.push_back(intersected);
}

void stepanchenko::print_linesCmd(std::vector< CrossRefs >& cross_refs, std::istream& in, std::ostream& out)
{
  std::string word, tName;
  in >> word >> tName;
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(),
    std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord = iterTable->search(word);
  std::vector< std::pair< size_t, std::string > > lines = iterTable->lines_;
  std::vector< std::pair< size_t, std::string > > t_lines;
  std::copy_if(lines.begin(), lines.end(), std::back_inserter(t_lines),
    std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  std::for_each(t_lines.begin(), t_lines.end(), [&](const std::pair<size_t, std::string>& line) {
    printL(line, out);
  });
}

void stepanchenko::printCmd(std::vector< CrossRefs >& cross_refs, std::istream& in, std::ostream& out)
{
  std::string tName;
  in >> tName;
  checkName(cross_refs, tName);
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(),
    std::bind(isName(), std::placeholders::_1, tName));
  iterTable->print(out);
}

void stepanchenko::delete_linesCmd(std::vector< CrossRefs >& cross_refs, std::istream& in)
{
  std::string word, tName;
  in >> word >> tName;
  checkName(cross_refs, tName);
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(),
    std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord = iterTable->search(word);
  auto iter = std::remove_if(iterTable->lines_.begin(), iterTable->lines_.end(),
    std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  iterTable->lines_.erase(iter, iterTable->lines_.end());
  iterTable->removeEntry(iterWord->first);
}

void stepanchenko::move_lines_downCmd(std::vector< CrossRefs >& cross_refs, std::istream& in)
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
  auto iterTable = std::find_if(cross_refs.begin(), cross_refs.end(),
    std::bind(isName(), std::placeholders::_1, tName));
  auto iterWord = iterTable->search(word);
  std::vector< std::pair< size_t, std::string > > t_lines;
  std::copy_if(iterTable->lines_.begin(), iterTable->lines_.end(), std::back_inserter(t_lines),
    std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  auto iter = std::remove_if(iterTable->lines_.begin(), iterTable->lines_.end(),
    std::bind(hasWord(), std::placeholders::_1, iterWord->second));
  iterTable->lines_.erase(iter, iterTable->lines_.end());

  std::move(iterTable->lines_.begin(), iterTable->lines_.end(), std::back_inserter(t_lines));
  iterTable->lines_ = t_lines;
  writeToFile(iterTable->getName(), iterTable->lines_, file);
  file.close();
}

void stepanchenko::viewCmd(std::vector< CrossRefs >& cross_refs, std::ostream& out)
{
  std::vector< std::string > names;
  std::transform(cross_refs.begin(), cross_refs.end(), std::back_inserter(names), std::bind(&CrossRefs::getName, std::placeholders::_1));
  std::copy(names.begin(), names.end(), std::ostream_iterator< std::string >(out, " "));
}

void stepanchenko::get_selectionCmd(std::vector< CrossRefs >& cross_refs, std::istream& in)
{
  std::string word1, word2, tName, rName;
  in >> word1 >> word2 >> tName >> rName;
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
  std::copy_if(iterTable->lines_.begin(), iterTable->lines_.end(),
    std::back_inserter(t_lines), std::bind(hasWord(), std::placeholders::_1, list));

  writeToFile(iterTable->getName(), t_lines, file);
}

void stepanchenko::saveCmd(std::istream& in, std::vector< CrossRefs >& cross_refs)
{
  std::string outputFileName;
  in >> outputFileName;

  std::ofstream outFile(outputFileName);

  if (!outFile.is_open())
  {
    throw std::logic_error("<INVALID COMMAND");
  }

  outFile << "\n--------Beginning of the table--------\n";
  for (const auto& cr : cross_refs)
  {
    outFile << cr.getName() << "\n";

    for (const auto& line : cr.lines_)
    {
      outFile << line.second << '\n';
    }

    outFile << "\n------------End of table------------\n";
  }

  outFile.close();
}
