#ifndef DATA_STRUCT_BUILDER_HPP
#define DATA_STRUCT_BUILDER_HPP

#include "dataStruct.hpp"
#include "keysEnum.hpp"

namespace demidenko
{
  struct KeyParser;
  struct FieldParser;

  class DataStructBuilder
  {
  public:
    DataStructBuilder(DataStruct& data);
    bool isDone() const noexcept;

  private:
    DataStruct& data_;
    KeysEnum current_key_;
    unsigned int keys_;

    friend std::istream& operator>>(std::istream& in, KeyParser&& parser);
    friend std::istream& operator>>(std::istream& in, FieldParser&& parser);
  };

  struct KeyParser
  {
    DataStructBuilder& builder_;
  };
  struct FieldParser
  {
    DataStructBuilder& builder_;
  };
}

#endif
