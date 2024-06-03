#include "table.hpp"
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <delimiters.hpp>

bool isAllowedSymbol(char symbol)
{
  return (std::isalnum(symbol)) || (symbol == '_');
}

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
      return std::stoull(first) == std::stoull(second);
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

bool isRowElementEqual(const babinov::Table::row_t& row, size_t index, const std::string& value, babinov::DataType dataType)
{
  return isEqual(row[index], value, dataType);
}

bool isRowElementByIteratorEqual(const std::pair< size_t, std::list< babinov::Table::row_t >::iterator >& pair, size_t index,
  const std::string& value, babinov::DataType dataType)
{
  return isRowElementEqual(*(pair.second), index, value, dataType);
}

template< class T >
void joinVectors(const std::vector< T >& vec1, const std::vector< T >& vec2, std::vector< T >& dest, size_t joinIndex)
{
  std::copy_n(vec1.cbegin(), joinIndex + 1, std::back_inserter(dest));
  std::copy(vec2.cbegin() + 1, vec2.cend(), std::back_inserter(dest));
  std::copy(vec1.cbegin() + joinIndex + 1, vec1.cend(), std::back_inserter(dest));
}

void fillWithDefaultValues(babinov::Table::row_t& dest, const std::vector< babinov::Column >& columns)
{
  for (auto it = columns.cbegin(); it != columns.cend(); ++it)
  {
    dest.push_back(babinov::DEFAULT_VALUES.at((*it).dataType));
  }
}

bool isInvalidColumn(const babinov::Column& column)
{
  return (!babinov::isCorrectName(column.name)) || (column.dataType == babinov::PK);
}

const std::string& getColumnName(const babinov::Column& column)
{
  return column.name;
}

const std::string& getRowValueByIndex(const babinov::Table::row_t& row, size_t index)
{
  return row[index];
}

std::list< babinov::Table::row_t >::const_iterator getRowIterator(const babinov::Table::row_t& row,
  const std::unordered_map< size_t, std::list< babinov::Table::row_t >::iterator >& rowIters)
{
  return rowIters.at(std::stoull(row[0]));
}

babinov::Table::row_t& replaceByDefault(babinov::Table::row_t& row, size_t index, babinov::DataType dataType)
{
  row[index] = babinov::DEFAULT_VALUES.at(dataType);
  return row;
}

size_t getIndexFromPair(std::pair< size_t, std::list< babinov::Table::row_t >::iterator > pair)
{
  return pair.first;
}

babinov::RowForIO getRowForIO(const babinov::Table::row_t& row, const std::vector< babinov::Column > columns)
{
  return babinov::RowForIO{columns, row};
}

namespace babinov
{
  bool isCorrectName(const std::string& name)
  {
    return std::all_of(name.cbegin(), name.cend(), isAllowedSymbol);
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

  bool Column::operator==(const Column& other) const
  {
    return (name == other.name) && (dataType == other.dataType);
  }

  bool Column::operator!=(const Column& other) const
  {
    return !(*this == other);
  }

  Table::Table():
    lastId_(0)
  {}

  Table::Table(std::vector< Column >::const_iterator begin, std::vector< Column >::const_iterator end):
    Table()
  {
    if (std::find_if(begin, end, isInvalidColumn) != end)
    {
      throw std::invalid_argument("Invalid columns");
    }
    std::vector< Column > tempColumns;
    tempColumns.push_back({"id", PK});
    std::copy(begin, end, std::back_inserter(tempColumns));
    columns_ = std::move(tempColumns);
  }

  Table::Table(const std::vector< Column >& columns):
    Table(columns.cbegin(), columns.cend())
  {}

  Table::Table(const Table& other):
    columns_(other.columns_),
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

  const std::vector< Column >& Table::getColumns() const
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
      if (!isCorrectValue(row[i], columns_[i + 1].dataType))
      {
        return false;
      }
    }
    return true;
  }

  size_t Table::getColumnIndex(const std::string& columnName) const
  {
    std::vector< std::string > columnNames;
    columnNames.reserve(columns_.size());
    std::transform(columns_.cbegin(), columns_.cend(), std::back_inserter(columnNames), getColumnName);
    auto it = std::find(columnNames.cbegin(), columnNames.cend(), columnName);
    if (it == columnNames.cend())
    {
      throw std::out_of_range("Column doesn't exist");
    }
    return it - columnNames.begin();
  }

  DataType Table::getColumnType(const std::string& columnName) const
  {
    return columns_[getColumnIndex(columnName)].dataType;
  }

  void Table::insert(const Table::row_t& row)
  {
    if (!isCorrectRow(row))
    {
      throw std::invalid_argument("Invalid row");
    }
    size_t pk = lastId_ + 1;
    row_t processed;
    processed.reserve(columns_.size());
    processed.push_back(std::to_string(pk));
    std::copy(row.cbegin(), row.cend(), std::back_inserter(processed));
    rows_.push_back(std::move(processed));
    rowIters_[pk] = std::prev(rows_.end());
    ++lastId_;
  }

  void Table::insert(const RowForIO& row)
  {
    size_t pk = std::stoull(row.values[0]);
    rows_.push_back(row.values);
    auto iter = std::prev(rows_.end());
    pk = std::stoull(row.values[0]);
    rowIters_[pk] = iter;
    lastId_ = std::max(lastId_, pk);
  }

  std::vector< std::list< Table::row_t >::const_iterator > Table::select(const std::string& columnName,
    const std::string& value) const
  {
    using namespace std::placeholders;
    size_t index = getColumnIndex(columnName);
    DataType dataType = columns_[index].dataType;
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
    std::vector< Table::row_t > fetched;
    auto pred = std::bind(isRowElementEqual, _1, index, value, dataType);
    std::copy_if(rows_.cbegin(), rows_.cend(), std::back_inserter(fetched), pred);
    auto pred2 = std::bind(getRowIterator, _1, std::cref(rowIters_));
    std::transform(fetched.cbegin(), fetched.cend(), std::back_inserter(result), pred2);
    return result;
  }

  bool Table::update(size_t rowId, const std::string& columnName, const std::string& value)
  {
    if (columnName == "id")
    {
      throw std::logic_error("Cannot update id field");
    }
    size_t index = getColumnIndex(columnName);
    if (!isCorrectValue(value, columns_[index].dataType))
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

  void Table::alter(const std::string& columnName, const Column& newColumn)
  {
    if (columnName == "id")
    {
      throw std::invalid_argument("Cannot alter id column");
    }
    if (newColumn.dataType == PK)
    {
      throw std::invalid_argument("Invalid column");
    }
    using namespace std::placeholders;
    size_t index = getColumnIndex(columnName);
    columns_[index] = newColumn;
    std::list< Table::row_t > rows;
    auto pred = std::bind(replaceByDefault, _1, index, getColumnType(newColumn.name));
    std::transform(rows_.begin(), rows_.end(), rows.begin(), pred);
  }

  bool Table::del(const std::string& columnName, const std::string& value)
  {
    size_t index = getColumnIndex(columnName);
    DataType dataType = columns_[index].dataType;
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
    using namespace std::placeholders;
    std::vector< std::pair< size_t, std::list< Table::row_t >::iterator > > pairsForRemoval;
    auto pred = std::bind(isRowElementByIteratorEqual, _1, index, value, dataType);
    std::copy_if(rowIters_.cbegin(), rowIters_.cend(), std::back_inserter(pairsForRemoval), pred);
    if (!pairsForRemoval.size())
    {
      return false;
    }
    std::vector< size_t > idsForRemoval(pairsForRemoval.size());
    std::transform(pairsForRemoval.begin(), pairsForRemoval.end(), std::back_inserter(idsForRemoval), getIndexFromPair);
    for (auto it = idsForRemoval.cbegin(); it != idsForRemoval.cend(); ++it)
    {
      rowIters_.erase(*it);
    }
    auto pred2 = std::bind(isRowElementEqual, _1, index, value, dataType);
    rows_.remove_if(pred2);
    return true;
  }

  void Table::swap(Table& other) noexcept
  {
    std::swap(columns_, other.columns_);
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
    size_t index = getColumnIndex(columnName);
    if (columns_[index].dataType != INTEGER)
    {
      throw std::invalid_argument("Column type must be integer");
    }
    std::vector< Column > newColumns;
    newColumns.reserve(columns_.size() + other.columns_.size() - 1);
    joinVectors(columns_, other.columns_, newColumns, index);
    Table newTable(newColumns.cbegin() + 1, newColumns.cend());
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

  TableHeader TableHeader::operator()(const std::pair< const std::string, Table > pair) const
  {
    return TableHeader{pair.first, pair.second.getColumns()};
  }

  std::istream& operator>>(std::istream& in, Column& column)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string dataType;
    std::getline(in, column.name, ':');
    in >> dataType;
    if (DATA_TYPES_FROM_STR.find(dataType) != DATA_TYPES_FROM_STR.cend())
    {
      column.dataType = DATA_TYPES_FROM_STR.at(dataType);
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, RowForIO& row)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using del = CharDelimiterI;
    std::string data;
    in >> del::insensitive('[');
    Table::row_t tempRow;
    for (size_t i = 0; i < row.columns.size(); ++i)
    {
      if (row.columns[i].dataType == TEXT)
      {
        in >> del::sensitive('\"');
        std::getline(in, data, '\"');
      }
      else
      {
        in >> data;
      }
      tempRow.push_back(data);
    }
    in >> del::insensitive(']');

    if (in)
    {
      row.values = std::move(tempRow);
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
    using input_column_it_t = std::istream_iterator< Column >;
    using del = StringDelimiterI;
    size_t nColumns = 0;
    in >> nColumns >> del::sensitive("COLUMNS:");
    std::vector< Column > columns;
    columns.reserve(nColumns);
    std::copy_n(input_column_it_t(in), nColumns, std::back_inserter(columns));
    if ((!nColumns) || (columns.size() != nColumns))
    {
      in.setstate(std::ios::failbit);
    }
    if (in.fail())
    {
      return in;
    }
    table = Table(columns.cbegin() + 1, columns.cend());
    RowForIO row{table.getColumns(), {}};
    while (in >> row)
    {
      table.insert(row);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Column& column)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << column.name << ':' << DATA_TYPES_AS_STR.at(column.dataType);
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const RowForIO& row)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << "[ ";
    for (size_t i = 0; i < row.columns.size(); ++i)
    {
      if (row.columns[i].dataType == TEXT)
      {
        out << '\"' << row.values[i] << '\"';
      }
      else
      {
        out << row.values[i];
      }
      out << ' ';
    }
    out << ']';
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Table& table)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    using namespace std::placeholders;
    using output_column_it_t = std::ostream_iterator< Column >;
    using output_row_it_t = std::ostream_iterator< RowForIO >;
    const std::vector< Column >& columns = table.getColumns();
    out << columns.size() << ' ' << "COLUMNS: ";
    std::copy(columns.cbegin(), columns.cend(), output_column_it_t(out, " "));
    out << '\n';
    const std::list< Table::row_t >& rows = table.getRows();
    std::vector< RowForIO > rowsForIO;
    rowsForIO.reserve(rows.size());
    auto pred = std::bind(getRowForIO, _1, table.getColumns());
    std::transform(rows.cbegin(), rows.cend(), std::back_inserter(rowsForIO), pred);
    std::copy(rowsForIO.cbegin(), rowsForIO.cend(), output_row_it_t(out, "\n"));
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const TableHeader& tableHeader)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    using output_it_t = std::ostream_iterator< Column >;
    out << "- " << tableHeader.name << "  [ ";
    std::copy(tableHeader.columns.cbegin(), tableHeader.columns.cend(), output_it_t(out, " "));
    out << ']';
    return out;
  }
}
