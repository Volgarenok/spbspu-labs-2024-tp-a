#ifndef DATA_STRUCT_BUILDER_HPP
#define DATA_STRUCT_BUILDER_HPP

#include "dataStruct.hpp"
#include "keysEnum.hpp"
namespace demidenko
{
  class DataStructBuilder
  {
  public:
    DataStructBuilder(DataStruct& data);
    bool isDone() const noexcept;

  private:
    DataStruct& data_;
    KeysEnum current_key_;
    unsigned int keys_;

    friend class FieldParser;
    friend class KeyParser;
  };

  class KeyParser
  {
  public:
    KeyParser(DataStructBuilder& builder);

  private:
    DataStructBuilder& builder_;
  };

  class FieldParser
  {
  public:
    FieldParser(DataStructBuilder& builder);

  private:
    DataStructBuilder& builder_;
  };

  std::istream& operator>>(std::istream& in, KeyParser&& parser);
  std::istream& operator>>(std::istream& in, FieldParser&& parser);
}
#endif
