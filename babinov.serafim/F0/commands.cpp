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
}
