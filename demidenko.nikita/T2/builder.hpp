#ifndef DATA_STRUCT_BUILDER_HPP
#define DATA_STRUCT_BUILDER_HPP

#include "dataStruct.hpp"
#include "keysEnum.hpp"

namespace demidenko
{
  struct KeyI;
  struct FieldI;
  std::istream& operator>>(std::istream& in, KeyI&& parser);
  std::istream& operator>>(std::istream& in, FieldI&& parser);

  class DataStructBuilder
  {
  public:
    DataStructBuilder(DataStruct& data);
    bool isDone() const noexcept;

  private:
    DataStruct& data_;
    KeysEnum current_key_;
    unsigned int keys_;

    friend std::istream& demidenko::operator>>(std::istream& in, KeyI&& parser);
    friend std::istream& demidenko::operator>>(std::istream& in, FieldI&& parser);
  };

  struct KeyI
  {
    DataStructBuilder& builder_;
  };
  struct FieldI
  {
    DataStructBuilder& builder_;
  };
}

#endif
