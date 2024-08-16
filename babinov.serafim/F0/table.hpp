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
  bool isLess(const std::string& el1, const std::string& el2, babinov::DataType dataType);

  const std::unordered_map< DataType, std::string > DEFAULT_VALUES = {
    {PK, "0"},
    {INTEGER, "0"},
    {REAL, "0.0"},
    {TEXT, ""}
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

  struct Column
  {
    std::string name;
    DataType dataType;
    bool operator==(const Column& other) const;
    bool operator!=(const Column& other) const;
  };

  struct RowForIO;

  class Table
  {
   public:
    using row_t = std::vector< std::string >;

    Table();
    Table(std::vector< Column >::const_iterator begin, std::vector< Column >::const_iterator end);
    explicit Table(const std::vector< Column >& columns);
    Table(const Table& other);
    Table(Table&& other) noexcept;
    ~Table() = default;
    Table& operator=(const Table& other);
    Table& operator=(Table&& other) noexcept;

    const std::vector< Column >& getColumns() const;
    const std::list< row_t >& getRows() const;
    bool isCorrectRow(const row_t& row) const;
    size_t getColumnIndex(const std::string& columnName) const;
    DataType getColumnType(const std::string& columnName) const;

    void insert(const row_t& row);
    void insert(const RowForIO& row);
    std::vector< std::list< row_t >::const_iterator > select(const std::string& columnName, const std::string& value) const;
    bool update(size_t rowId, const std::string& columnName, const std::string& value);
    void alter(const std::string& columnName, const Column& newColumn);
    bool del(const std::string& columnName, const std::string& value);
    void swap(Table& other) noexcept;
    void clear() noexcept;

    template< class Comparator >
    void sort(const std::string& columnName, Comparator comp);
    void sort(const std::string& columnName);
    Table link(const Table& other, const std::string& columnName) const;

   private:
    std::vector< Column > columns_;
    std::list< row_t > rows_;
    std::unordered_map< size_t, std::list< row_t >::iterator > rowIters_;
    size_t lastId_;
  };

  template< class Comparator >
  void Table::sort(const std::string& columnName, Comparator comp)
  {
    size_t index = getColumnIndex(columnName);
    auto pred = [&](const row_t& r1, const row_t& r2) -> bool
    {
      return comp(r1[index], r2[index]);
    };
    rows_.sort(pred);
  }

  struct RowForIO
  {
    std::vector< Column > columns;
    Table::row_t values;
  };

  struct TableHeader
  {
    std::string name;
    std::vector< Column > columns;
    TableHeader operator()(const std::pair< const std::string, Table > pair) const;
  };

  bool isCorrectName(const std::string& name);
  bool isLess(const std::string& el1, const std::string& el2, DataType dataType);
  std::istream& operator>>(std::istream& in, Column& column);
  std::istream& operator>>(std::istream& in, RowForIO& row);
  std::istream& operator>>(std::istream& in, Table& table);
  std::ostream& operator<<(std::ostream& out, const Column& column);
  std::ostream& operator<<(std::ostream& out, const RowForIO& row);
  std::ostream& operator<<(std::ostream& out, const Table& table);
  std::ostream& operator<<(std::ostream& out, const TableHeader& tableHeader);
}

#endif
