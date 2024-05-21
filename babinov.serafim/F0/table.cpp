#include "table.hpp"
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <delimiters.hpp>

bool isCorrectValue(const std::string& value, babinov::DataType dataType)
{
  size_t size = value.size();
  size_t* pos = &size;
  try
  {
    if (dataType == babinov::PK)
    {
      if (value.size() && value[0] == '-')
      {
        return false;
      }
      std::stoull(value, pos);
    }
    else if (dataType == babinov::INTEGER)
    {
      std::stoi(value, pos);
    }
    else if (dataType == babinov::REAL)
    {
      std::stod(value, pos);
    }
    return *pos == value.size();
  }
  catch (const std::invalid_argument&)
  {
    return false;
  }
}

bool isEqual(const std::string& first, const std::string& second, babinov::DataType dataType)
{
  try
  {
    if (dataType == babinov::PK)
    {
      return std::stoull(first) == std::stoull(first);
    }
    else if (dataType == babinov::INTEGER)
    {
      return std::stoi(first) == std::stoi(second);
    }
    else if (dataType == babinov::REAL)
    {
      return std::stod(first) == std::stod(second);
    }
    return first == second;
  }
  catch (const std::invalid_argument&)
  {
    return false;
  }
}

template< class T >
void joinVectors(const std::vector< T >& vec1, const std::vector< T >& vec2, std::vector< T >& dest, size_t joinIndex)
{
  std::copy_n(vec1.cbegin(), joinIndex + 1, std::back_inserter(dest));
  std::copy(vec2.cbegin() + 1, vec2.cend(), std::back_inserter(dest));
  std::copy(vec1.cbegin() + joinIndex + 1, vec1.cend(), std::back_inserter(dest));
}

void fillWithDefaultValues(babinov::Table::row_t& dest, const std::vector< babinov::Table::column_t >& columns)
{
  for (auto it = columns.cbegin(); it != columns.cend(); ++it)
  {
    dest.push_back(babinov::DEFAULT_VALUES.at((*it).second));
  }
}

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

  bool isLess(const std::string& el1, const std::string& el2, DataType dataType)
  {
    if (dataType == PK)
    {
      return std::stoull(el1) < std::stoull(el2);
    }
    else if (dataType == INTEGER)
    {
      return std::stoi(el1) < std::stoi(el2);
    }
    else if (dataType == REAL)
    {
      return std::stod(el1) < std::stod(el2);
    }
    return el1 < el2;
  }

  Table::Table():
    lastId_(0)
  {}

  Table::Table(const std::vector< column_t >& columns):
    Table()
  {
    std::unordered_map< std::string, size_t > cIndexes;
    std::vector< column_t > tempColumns;
    tempColumns.push_back({"id", PK});
    cIndexes.insert({"id", 0});
    size_t i = (columns[0] == std::pair< std::string, DataType >("id", PK)) ? 1 : 0;
    for (; i < columns.size(); ++i)
    {
      if ((!isCorrectName(columns[i].first)) || (columns[i].second == PK) || (cIndexes.find(columns[i].first) != cIndexes.end()))
      {
        throw std::invalid_argument("Invalid columns");
      }
      cIndexes[columns[i].first] = i + 1;
      tempColumns.push_back(columns[i]);
    }
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

  const std::vector< Table::column_t >& Table::getColumns() const
  {
    return columns_;
  }

  const std::list< Table::row_t >& Table::getRows() const
  {
    return rows_;
  }

  bool Table::isCorrectRow(const Table::row_t& row) const
  {
    if (row.size() != (columns_.size() - 1))
    {
      return false;
    }
    for (size_t i = 0; i < row.size(); ++i)
    {
      if (!isCorrectValue(row[i], columns_[i + 1].second))
      {
        return false;
      }
    }
    return true;
  }

  DataType Table::getColumnType(const std::string& columnName) const
  {
    return columns_[columnIndexes_.at(columnName)].second;
  }

  void Table::printRow(std::ostream& out, const Table::row_t& row) const
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return;
    }
    out << "[ ";
    for (size_t i = 0; i < columns_.size(); ++i)
    {
      if (columns_[i].second == TEXT)
      {
        out << '\"' << row[i] << '\"';
      }
      else
      {
        out << row[i];
      }
      out << ' ';
    }
    out << ']';
  }

  void Table::printRow(std::ostream& out, std::list< row_t >::const_iterator iter) const
  {
    printRow(out, *iter);
  }

  void Table::insert(const Table::row_t& row)
  {
    if (!isCorrectRow(row))
    {
      throw std::invalid_argument("Invalid row");
    }
    size_t pk = lastId_ + 1;
    row_t processed;
    processed.push_back(std::to_string(pk));
    std::copy(row.cbegin(), row.cend(), std::back_inserter(processed));
    rows_.push_back(std::move(processed));
    rowIters_[pk] = std::prev(rows_.end());;
    ++lastId_;
  }

  std::vector< std::list< Table::row_t >::const_iterator  > Table::select(const std::string& columnName,
    const std::string& value) const
  {
    size_t index = columnIndexes_.at(columnName);
    DataType dataType = columns_[index].second;
    if (!isCorrectValue(value, dataType))
    {
      throw std::invalid_argument("Invalid value");
    }
    std::vector< std::list< Table::row_t >::const_iterator > result;
    if (columnName == "id")
    {
      size_t pk = std::stoull(value);
      auto desired = rowIters_.find(pk);
      if (desired != rowIters_.cend())
      {
        result.push_back((*desired).second);
      }
      return result;
    }
    for (auto it = rows_.begin(); it != rows_.end(); ++it)
    {
      if (isEqual((*it)[index], value, dataType))
      {
        result.push_back(it);
      }
    }
    return result;
  }

  bool Table::update(size_t rowId, const std::string& columnName, const std::string& value)
  {
    if (columnName == "id")
    {
      throw std::logic_error("Cannot update id field");
    }
    size_t index = columnIndexes_.at(columnName);
    if (!isCorrectValue(value, columns_[index].second))
    {
      throw std::invalid_argument("Invalid value");
    }
    try
    {
      (*rowIters_.at(rowId))[index] = value;
      return true;
    }
    catch (const std::out_of_range&)
    {
      return false;
    }
  }

  bool Table::del(const std::string& columnName, const std::string& value)
  {
    size_t index = columnIndexes_.at(columnName);
    DataType dataType = columns_[index].second;
    if (!isCorrectValue(value, dataType))
    {
      throw std::invalid_argument("Invalid value");
    }
    if (columnName == "id")
    {
      size_t pk = std::stoull(value);
      auto desired = rowIters_.find(pk);
      if (desired != rowIters_.end())
      {
        rows_.erase((*desired).second);
        rowIters_.erase(pk);
        return true;
      }
      return false;
    }
    bool isDeleted = false;
    auto it = rows_.begin();
    while (it != rows_.end())
    {
      auto temp = it;
      ++it;
      if (isEqual((*temp)[index], value, dataType))
      {
        size_t pk = std::stoull((*temp)[0]);
        rows_.erase(temp);
        rowIters_.erase(pk);
        isDeleted = true;
      }
    }
    return isDeleted;
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

  void Table::clear() noexcept
  {
    rows_.clear();
    rowIters_.clear();
    lastId_ = 0;
  }

  void Table::sort(const std::string& columnName)
  {
    using namespace std::placeholders;
    auto comp = std::bind(isLess, _1, _2, getColumnType(columnName));
    return sort(columnName, comp);
  }

  Table Table::link(const Table& other, const std::string& columnName) const
  {
    if (columnName == "id")
    {
      throw std::invalid_argument("Cannot link by id column");
    }
    size_t index = columnIndexes_.at(columnName);
    if (columns_[index].second != INTEGER)
    {
      throw std::invalid_argument("Column type must be integer");
    }
    std::vector< column_t > newColumns;
    newColumns.reserve(columns_.size() + other.columns_.size() - 1);
    joinVectors(columns_, other.columns_, newColumns, index);
    Table newTable(std::move(newColumns));
    for (auto it = rows_.cbegin(); it != rows_.cend(); ++it)
    {
      size_t pk = std::stoull((*it)[index]);
      row_t row;
      row.reserve(columns_.size() + other.columns_.size() - 1);
      if (other.rowIters_.find(pk) != other.rowIters_.end())
      {
        joinVectors(*it, *(other.rowIters_.at(pk)), row, index);
      }
      else
      {
        Table::row_t defaultRow;
        fillWithDefaultValues(defaultRow, other.columns_);
        joinVectors(*it, std::move(defaultRow), row, index);
      }
      newTable.rows_.push_back(std::move(row));
      newTable.rowIters_[std::stoull((*it)[0])] = std::prev(newTable.rows_.end());
      ++newTable.lastId_;
    }
    return newTable;
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

  std::ostream& operator<<(std::ostream& out, const Table::column_t& column)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << column.first << ':' << DATA_TYPES_AS_STR.at(column.second);
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Table& table)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    using output_it_t = std::ostream_iterator< Table::column_t >;
    const std::vector< Table::column_t >& columns = table.getColumns();
    out << columns.size() << ' ' << "COLUMNS: ";
    std::copy(columns.cbegin(), columns.cend(), output_it_t(out, " "));
    const std::list< Table::row_t >& rows = table.getRows();
    for (auto it = rows.cbegin(); it != rows.cend(); ++it)
    {
      out << '\n';
      table.printRow(out, it);
    }
    return out;
  }
}
