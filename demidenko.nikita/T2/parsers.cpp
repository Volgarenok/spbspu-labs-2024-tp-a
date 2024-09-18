#include "parsers.hpp"
#include <istream>
#include <delimeter.hpp>
#include "dataStruct.hpp"
#include "keysEnum.hpp"

template <>
void demidenko::KeyI::parse(std::istream& in)
{
  int key_number = 0;
  in >> DelimeterI{ "key" } >> key_number;
  if (key_number < 1 || in.fail())
  {
    in.setstate(std::ios::failbit);
    return;
  }
  key_number = 1 << (key_number - 1);

  bool is_in_range = key_number && key_number < KeysEnum::ALL;
  if (!is_in_range)
  {
    in.setstate(std::ios::failbit);
    return;
  }
  data = static_cast< KeysEnum >(key_number);
}

template <>
void demidenko::ComplexI::parse(std::istream& in)
{
  using del = DelimeterI;
  double real = 0.0;
  double imaginary = 0.0;
  in >> std::fixed;
  in >> del{ "#c(" } >> real;
  in >> del{ " " } >> imaginary >> del{ ")" };
  data = std::complex< double >(real, imaginary);
}

template <>
void demidenko::UnsignedLongLongI::parse(std::istream& in)
{
  in >> DelimeterI{ "0" } >> std::oct >> data;
}

template <>
void demidenko::StringI::parse(std::istream& in)
{
  in >> DelimeterI{ "\"" };
  std::getline(in, data, '"');
}
