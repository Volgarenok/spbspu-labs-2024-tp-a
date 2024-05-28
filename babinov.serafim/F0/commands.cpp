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

void readCondition(std::istream& in, const babinov::Table& table, std::string& columnName, std::string& value)
{
  std::getline(in, columnName, '=');
  try
  {
    babinov::DataType dataType = table.getColumnType(columnName);
    readValue(in, value, dataType);
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("<ERROR: INVALID COLUMN>");
  }
}

namespace babinov
{
  void execCmdTables(const std::unordered_map< std::string, Table >& tables, std::ostream& out)
  {
    using output_it_t = std::ostream_iterator< Column >;
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
    using input_it_t = std::istream_iterator< Column >;
    std::string tableName;
    in >> tableName;
    if (tables.find(tableName) != tables.end())
    {
      throw std::invalid_argument("<ERROR: TABLE ALREADY EXISTS>");
    }
    size_t nColumns = 0;
    std::vector< Column > columns;
    in >> nColumns;
    try
    {
      columns.reserve(nColumns + 1);
    }
    catch(const std::length_error&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMNS>");
    }
    std::copy_n(input_it_t(in), nColumns, std::back_inserter(columns));
    if ((!in) || (!columns.size()))
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
    const std::vector< Column >& columns = tables[tableName].getColumns();
    row.reserve(columns.size());
    for (size_t i = 1; i < columns.size(); ++i)
    {
      std::string data;
      readValue(in, data, columns[i].dataType);
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

  void execCmdSelect(const std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    const Table& table = tables.at(tableName);
    std::string columnName;
    std::string value;
    in.get();
    readCondition(in, table, columnName, value);
    try
    {
      std::vector< std::list< Table::row_t >::const_iterator > selection = table.select(columnName, value);
      for (auto it = selection.cbegin(); it != selection.cend(); ++it)
      {
        table.printRow(out, *it);
        out << '\n';
      }
    }
    catch (const std::out_of_range&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<ERROR: INVALID VALUE>");
    }
  }

  void execCmdUpdate(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    Table& table = tables[tableName];
    size_t id = 0;
    in >> id;
    if (!in)
    {
      throw std::invalid_argument("<ERROR: INVALID ID>");
    }
    std::string columnName;
    in >> columnName;
    bool isUpdated = false;
    try
    {
      std::string value;
      readValue(in, value, table.getColumnType(columnName));
      isUpdated = table.update(id, columnName, std::move(value));
    }
    catch (const std::out_of_range&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<ERROR: INVALID VALUE>");
    }
    catch (const std::logic_error&)
    {
      throw std::invalid_argument("<ERROR: CANNOT UPDATE ID FIELD>");
    }
    if (!isUpdated)
    {
      throw std::invalid_argument("<ERROR: INVALID ID>");
    }
    out << "<SUCCESSFULLY UPDATED>" << '\n';
  }

  void execCmdAlter(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    Column newColumn;
    std::string columnName;
    in >> newColumn >> columnName;
    if (!in)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    try
    {
      tables[tableName].alter(columnName, newColumn);
    }
    catch(const std::invalid_argument&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    out << "<SUCCESSFULLY UPDATED>" << '\n';
  }

  void execCmdDelete(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    Table& table = tables[tableName];
    std::string columnName;
    std::string value;
    in.get();
    readCondition(in, table, columnName, value);
    try
    {
      bool isDeleted = table.del(columnName, value);
      if (isDeleted)
      {
        out << "<SUCCESSFULLY DELETED>" << '\n';
      }
      else
      {
        out << "<THERE ARE NOT ROWS WITH SPECIFIED CONDITION>" << '\n';
      }
    }
    catch (const std::out_of_range&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<ERROR: INVALID VALUE>");
    }
  }

  void execCmdClear(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    tables[tableName].clear();
    out << "<SUCCESSFULLY CLEARED>" << '\n';
  }

  void execCmdSave(const std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    std::string fileName;
    in >> fileName;
    std::ofstream file(fileName);
    file << tables.at(tableName);
    out << "<SUCCESSFULLY SAVED>" << '\n';
  }

  void execCmdClose(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string tableName;
    readTableName(in, tables, tableName);
    out << "Are you sure you want to close this table (Y/N)?" << '\n' << "> ";
    std::string answer;
    in >> answer;
    if ((answer == "Y") || (answer == "y"))
    {
      tables.erase(tableName);
      out << "<TABLE SUCCESFULLY CLOSED>" << '\n';
    }
  }

  void execCmdSort(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    char order = 0;
    std::string columnName;
    std::string tableName;
    readTableName(in, tables, tableName);
    in >> order;
    in >> columnName;
    if ((order != '>') && (order != '<'))
    {
      throw std::invalid_argument("<ERROR: TYPE OF SORT IS INVALID>");
    }
    try
    {
      if (order == '>')
      {
        tables[tableName].sort(columnName);
      }
      else
      {
        using namespace std::placeholders;
        auto comp = std::bind(isLess, _2, _1, tables[tableName].getColumnType(columnName));
        tables[tableName].sort(columnName, comp);
      }
    }
    catch(const std::out_of_range&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    out << "<TABLE SUCCESFULLY SORTED>" << '\n';
  }

  void execCmdLink(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out)
  {
    std::string firstTableName;
    std::string secondTableName;
    std::string newTableName;
    std::string columnName;
    readTableName(in, tables, firstTableName);
    readTableName(in, tables, secondTableName);
    in >> newTableName >> columnName;
    if (!isCorrectName(newTableName))
    {
      throw std::invalid_argument("<ERROR: INVALID TABLE NAME>");
    }
    try
    {
      Table newTable = tables[firstTableName].link(tables[secondTableName], columnName);
      tables[newTableName] = std::move(newTable);
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<ERROR: INVALID COLUMN>");
    }
    out << "<TABLES WERE SUCCESFULLY LINKED>" << '\n';
  }
}