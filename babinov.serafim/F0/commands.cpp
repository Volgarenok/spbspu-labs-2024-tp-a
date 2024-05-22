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
}
