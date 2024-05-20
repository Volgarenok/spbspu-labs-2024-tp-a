#include "table.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <delimiters.hpp>

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

  Table& Table::operator=(const Table& other)
  {
    if (this != &other)
    {
      Table temp(other);
      swap(temp);
    }
    return *this;
  }

  Table& Table::operator=(Table&& other) noexcept
  {
    if (this != &other)
    {
      Table temp(std::move(other));
      swap(temp);
    }
    return *this;
  }

  void Table::readRow(std::istream& in)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return;
    }
    using del = CharDelimiterI;
    std::string data;
    in >> del::insensitive('[') >> data;
    size_t pk = std::stoull(data);

    Table::row_t row;
    row.push_back(data);

    for (size_t i = 1; i < columns_.size(); ++i)
    {
      if (columns_[i].second == TEXT)
      {
        in >> del::sensitive('\"');
        std::getline(in, data, '\"');
      }
      else
      {
        in >> data;
      }
      row.push_back(data);
    }
    in >> del::insensitive(']');

    if (in)
    {
      rows_.push_back(std::move(row));
      auto iter = std::prev(rows_.end());
      rowIters_[pk] = iter;
      lastId_ = std::max(lastId_, pk);
    }
  }

  void Table::swap(Table& other) noexcept
  {
    std::swap(columns_, other.columns_);
    std::swap(columnIndexes_, other.columnIndexes_);
    std::swap(rows_, other.rows_);
    std::swap(rowIters_, other.rowIters_);
    std::swap(lastId_, other.lastId_);
  }

  std::istream& operator>>(std::istream& in, Table::column_t& column)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using del = CharDelimiterI;
    std::string dataType;
    std::getline(in, column.first, ':');
    in >> dataType;
    if (DATA_TYPES_FROM_STR.find(dataType) != DATA_TYPES_FROM_STR.cend())
    {
      column.second = DATA_TYPES_FROM_STR.at(dataType);
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Table& table)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using input_it_t = std::istream_iterator< Table::column_t >;
    using del = StringDelimiterI;
    size_t nColumns = 0;
    in >> nColumns >> del::sensitive("COLUMNS:");
    std::vector< Table::column_t > columns;
    Table::column_t column;
    in >> column;
    std::copy_n(input_it_t(in), nColumns, std::back_inserter(columns));
    table = Table(std::move(columns));
    while (in)
    {
      table.readRow(in);
    }
    return in;
  }
}
