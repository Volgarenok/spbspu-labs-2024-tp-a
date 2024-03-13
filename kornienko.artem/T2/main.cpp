#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iomanip>

struct DataStruct
{
  double key1;
  unsigned long long key2;
  std::string key3;
};

struct Delimeter
{
  char expected;
};

struct DelimeterIgnoreRegister
{
  char expected;
};

struct DelimeterString
{
  std::string expected;
};

std::istream & operator>>(std::istream & in, const Delimeter && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & operator>>(std::istream & in, const DelimeterIgnoreRegister && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (std::tolower(c) != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & operator>>(std::istream & in, const DelimeterString && exp)
{
  using del = Delimeter;
  for (int i = 0;exp.expected[i] != '\0' && in; ++i)
  {
    in >> del{exp.expected[i]};
  }
  return in;
}

std::istream & operator>>(std::istream & in, DataStruct & value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimeter;
  using delIR = DelimeterIgnoreRegister;
  using delStr = DelimeterString;
  std::size_t NUMBER_OF_KEYS = 3;
  int c = 0;
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3 = "";
  in >> del{'('};
  for (int i = 0; i < NUMBER_OF_KEYS; ++i)
  {
    in >> delStr{":key"} >> c;
    switch (c)
    {
    case 1:
      in >> key1 >> delIR{ 'd' };
      break;
    case 2:
      in >> std::hex >> key2;
      break;
    case 3:
      in >> del{'"'};
      std::getline(in, key3, '"');
      break;
    default:
      break;
    }
  }
  in >> delStr{":)"};
  if (in)
  {
    value.key1 = key1;
    value.key2 = key2;
    value.key3 = key3;
  }
  return in;
}

std::ostream & operator<<(std::ostream & out, const DataStruct & value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << std::setprecision(1) << std::fixed << value.key1 << "d";
  out << std::uppercase << ":key2 0x" << std::hex << value.key2;
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}

int main()
{
  using input_it_t = std::istream_iterator< DataStruct >;
  std::vector< DataStruct > data(input_it_t{std::cin}, input_it_t{});

  using output_it_t = std::ostream_iterator< DataStruct  >;
  std::copy(data.cbegin(), data.cend(), output_it_t{std::cout, "\n"});
  return 0;
}
