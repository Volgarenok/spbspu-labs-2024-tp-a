#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <unordered_map>

#include "delimiters.hpp"
#include "table.hpp"

void readTableName(std::istream& in, const std::unordered_map< std::string, babinov::Table >& tables, std::string& dest)
{
  in >> dest;
  if (tables.find(dest) == tables.end())
  {
    throw std::invalid_argument("<ERROR: TABLE DOESN'T EXIST>");
  }
}

void readValue(std::istream& in, std::string& value, babinov::DataType dataType)
{
  using del = babinov::CharDelimiterI;
  if (dataType == babinov::TEXT)
  {
    in >> del::sensitive('\"');
    if (in)
    {
      std::getline(in, value, '\"');
    }
  }
  else
  {
    in >> value;
  }
  if (!in)
  {
    throw std::invalid_argument("<ERROR: INVALID VALUE>");
  }
}

namespace babinov
{
  void execCmdTables(const std::unordered_map< std::string, Table >& tables, std::ostream& out)
  {
    using output_it_t = std::ostream_iterator< Table::column_t >;
    for (auto it = tables.cbegin(); it != tables.cend(); ++it)
    {
      out << "- " << (*it).first << "  [ ";
      std::copy((*it).second.getColumns().cbegin(), (*it).second.getColumns().cend(), output_it_t(out, " "));
      out << ']' << '\n';
    }
  }

  void execCmdLoad(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string fileName;
    std::string tableName;
    in >> fileName >> tableName;
    if (!isCorrectName(tableName))
    {
      throw std::invalid_argument("<ERROR: INVALID TABLE NAME>");
    }
    std::ifstream file(fileName);
    if (!file.is_open())
    {
      throw std::invalid_argument("<ERROR: FILE DOESN'T EXIST>");
    }
    if (tables.find(tableName) != tables.end())
    {
      throw std::invalid_argument("<ERROR: TABLE ALREADY EXISTS>");
    }
    Table newTable;
    file >> newTable;
    if ((!file.eof()) || (!newTable.getColumns().size()))
    {
      throw std::invalid_argument("<ERROR: INVALID TABLE>");
    }
    tables[tableName] = std::move(newTable);
    out << "<SUCCESSFULLY LOADED>" << '\n';
  }

  void execCmdCreate(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    in >> tableName;
    if (tables.find(tableName) != tables.end())
    {
      throw std::invalid_argument("<ERROR: TABLE ALREADY EXISTS>");
    }
    std::vector< Table::column_t > columns;
    while (in && (in.peek() != '\n'))
    {
      Table::column_t column;
      in >> column;
      columns.push_back(column);
    }
    if (!in)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMNS>");
    }
    try
    {
      tables[tableName] = Table(std::move(columns));
      out << "<SUCCESSFULLY CREATED>" << '\n';
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMNS>");
    }
  }

  void execCmdInsert(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    Table::row_t row;
    const std::vector< Table::column_t >& columns = tables[tableName].getColumns();
    for (size_t i = 1; i < columns.size(); ++i)
    {
      std::string data;
      readValue(in, data, columns[i].second);
      row.push_back(data);
    }
    try
    {
      tables[tableName].insert(std::move(row));
      out << "<SUCCESSFULLY INSERTED>" << '\n';
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<ERROR: INVALID VALUE>");
    }
  }
}
