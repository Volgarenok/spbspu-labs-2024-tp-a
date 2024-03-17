#include "dataStructBuilder.hpp"
#include "dataStruct.hpp"
#include "delimeter.hpp"
#include "keysEnum.hpp"
#include "streamGuard.hpp"

demidenko::DataStructBuilder::DataStructBuilder(DataStruct& data):
  data_(data),
  current_key_(demidenko::KeysEnum::NONE),
  keys_(0)
{}
bool demidenko::DataStructBuilder::isDone() const noexcept
{
  return keys_ == demidenko::KeysEnum::ALL;
}

std::istream& demidenko::operator>>(std::istream& in, KeyParser&& parser)
{
  if (parser.builder_.isDone())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  demidenko::StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int key_number = 0;
  in >> DelimeterI{"key"} >> key_number;
  key_number <<= key_number;
  if (!key_number || key_number > demidenko::KeysEnum::ALL)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  parser.builder_.current_key_ = static_cast< KeysEnum >(key_number);
  return in;
}

std::istream& demidenko::operator>>(std::istream& in, FieldParser&& parser);
