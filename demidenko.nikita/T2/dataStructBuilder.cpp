#include "dataStructBuilder.hpp"
#include <complex>
#include <iomanip>
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
  demidenko::StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int key_number = 0;
  in >> DelimeterI{"key"} >> key_number;
  if (key_number < 1 || in.fail())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  key_number = 1 << (key_number - 1);

  bool is_in_range = !key_number || key_number > demidenko::KeysEnum::ALL;
  bool is_unique = !(key_number & parser.builder_.keys_);
  if (!(is_in_range || is_unique))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  parser.builder_.current_key_ = static_cast< KeysEnum >(key_number);
  return in;
}

std::istream& demidenko::operator>>(std::istream& in, FieldParser&& parser)
{
  demidenko::StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  KeysEnum key = parser.builder_.current_key_;
  DataStruct& data = parser.builder_.data_;
  using del = DelimeterI;
  switch (key)
  {
  case ULL_OCT:
    in >> del{"0"} >> std::oct >> data.key1;
    break;
  case CMP_LSP:
  {
    in >> del{"#c("} >> std::setprecision(1);
    double real = 0.0;
    double imaginary = 0.0;
    in >> real >> del{" "} >> imaginary >> del{")"};
    data.key2 = std::complex< double >(real, imaginary);
    break;
  }
  case STRING:
    in >> del{"\""} >> data.key3 >> del{"\""};
    break;
  default:
    in.setstate(std::ios::failbit);
    return in;
  }

  if (in.good())
  {
    parser.builder_.keys_ |= key;
  }
  return in;
}
