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

    void swap(Table& other) noexcept;
   private:
    std::vector< column_t > columns_;
    std::unordered_map< std::string, size_t > columnIndexes_;
    std::list< row_t > rows_;
    std::unordered_map< size_t, std::list< row_t >::iterator > rowIters_;
    size_t lastId_;
  };
}

#endif
