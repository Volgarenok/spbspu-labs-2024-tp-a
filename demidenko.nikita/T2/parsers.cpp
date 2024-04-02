#include "parsers.hpp"
#include <istream>
#include "dataStruct.hpp"
#include "delimeter.hpp"
#include "keysEnum.hpp"
#include "streamGuard.hpp"

std::istream& demidenko::operator>>(std::istream& in, KeyI&& parser)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int key_number = 0;
  in >> DelimeterI{ "key" } >> key_number;
  if (key_number < 1 || in.fail())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  key_number = 1 << (key_number - 1);

  bool is_in_range = !key_number || key_number > KeysEnum::ALL;
  if (!is_in_range)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  parser.key = static_cast< KeysEnum >(key_number);
  return in;
}

std::istream& demidenko::operator>>(std::istream& in, ComplexI&& parser)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using del = DelimeterI;
  double real = 0.0;
  double imaginary = 0.0;
  in >> std::fixed;
  in >> del{ "#c(" } >> real;
  in >> del{ " " } >> imaginary >> del{ ")" };
  parser.complex = std::complex< double >(real, imaginary);
  return in;
}

std::istream& demidenko::operator>>(std::istream& in, UnsignedLongLongI&& parser)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> DelimeterI{ "0" } >> std::oct >> parser.ull;
  return in;
}

std::istream& demidenko::operator>>(std::istream& in, StringI&& parser)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> DelimeterI{ "\"" };
  std::getline(in, parser.str, '"');
  return in;
}
