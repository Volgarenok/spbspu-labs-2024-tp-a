#ifndef TABLE_HPP
#define TABLE_HPP
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace babinov
{
  enum DataType
  {
    PK,
    INTEGER,
    REAL,
    TEXT
  };

  const std::unordered_map< DataType, std::string > DATA_TYPES_AS_STR = {
    {PK, "PK"},
    {INTEGER, "INTEGER"},
    {REAL, "REAL"},
    {TEXT, "TEXT"}
  };

  const std::unordered_map< std::string, DataType > DATA_TYPES_FROM_STR = {
    {"PK", PK},
    {"INTEGER", INTEGER},
    {"REAL", REAL},
    {"TEXT", TEXT}
  };

  class Table
  {
   public:
    using column_t = std::pair< std::string, DataType >;
    using row_t = std::vector< std::string >;

    Table();
    explicit Table(const std::vector< column_t >& columns);
    Table(const Table& other);
    Table(Table&& other) noexcept;
    ~Table() = default;
    Table& operator=(const Table& other);
    Table& operator=(Table&& other) noexcept;

    const std::vector< column_t >& getColumns() const;
    const std::list< row_t >& getRows() const;

    void readRow(std::istream& in);
    void printRow(std::ostream& out, std::list< row_t >::const_iterator iter) const;
    void printRow(std::ostream& out, const Table::row_t& row) const;

    void swap(Table& other) noexcept;
   private:
    std::vector< column_t > columns_;
    std::unordered_map< std::string, size_t > columnIndexes_;
    std::list< row_t > rows_;
    std::unordered_map< size_t, std::list< row_t >::iterator > rowIters_;
    size_t lastId_;
  };
  std::istream& operator>>(std::istream& in, Table::column_t& column);
  std::istream& operator>>(std::istream& in, Table& table);
  std::ostream& operator<<(std::ostream& out, const Table::column_t& column);
  std::ostream& operator<<(std::ostream& out, const Table& table);
}

#endif
