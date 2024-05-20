#include "table.hpp"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <stdexcept>

namespace babinov
{
  bool isCorrectName(const std::string& name)
  {
    auto pred = [](const char ch) -> bool
    {
      return !((std::isalnum(ch)) || (ch == '_'));
    };
    return (std::find_if(name.cbegin(), name.cend(), pred)) == (name.cend());
  }

  Table::Table():
    lastId_(0)
  {}

  Table::Table(const std::vector< column_t >& columns):
    Table()
  {
    std::unordered_map< std::string, size_t > cIndexes;
    cIndexes.insert({"id", 0});
    for (size_t i = 0; i < columns.size(); ++i)
    {
      if ((!isCorrectName(columns[i].first)) || (columns[i].second == PK) || (cIndexes.find(columns[i].first) != cIndexes.end()))
      {
        throw std::invalid_argument("Invalid columns");
      }
      cIndexes[columns[i].first] = i + 1;
    }
    std::vector< column_t > tempColumns;
    tempColumns.push_back({"id", PK});
    std::copy(columns.cbegin(), columns.cend(), std::back_inserter(tempColumns));
    columns_ = std::move(tempColumns);
    columnIndexes_ = std::move(cIndexes);
  }

  Table::Table(const Table& other):
    columns_(other.columns_),
    columnIndexes_(other.columnIndexes_),
    rows_(other.rows_),
    lastId_(other.lastId_)
  {
    for (auto it = rows_.begin(); it != rows_.end(); ++it)
    {
      rowIters_.insert({std::stoull((*it)[0]), it});
    }
  }

  Table::Table(Table&& other) noexcept:
    columns_(std::move(other.columns_)),
    columnIndexes_(std::move(other.columnIndexes_)),
    rows_(std::move(other.rows_)),
    rowIters_(std::move(other.rowIters_)),
    lastId_(other.lastId_)
  {
    other.lastId_ = 0;
  }
}
