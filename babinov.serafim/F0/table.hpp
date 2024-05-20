#ifndef TABLE_HPP
#define TABLE_HPP
#include <string>
#include <unordered_map>

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
}

#endif
