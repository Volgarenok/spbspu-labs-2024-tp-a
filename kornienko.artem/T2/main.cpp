#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>

struct DataStruct
{
  double key1;
  unsigned long long key2;
  std::string key3;
};

struct DelimeterI
{
  char expected;
};

struct DelimeterIgnoreRegister
{
  char expected;
};

std::istream & operator>>(std::istream & in, DelimeterI && exp)
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

std::istream & operator>>(std::istream & in, DelimeterIgnoreRegister && exp)
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

std::istream & operator>>(std::istream & in, DataStruct & value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimeterI;
  using delIgnReg = DelimeterIgnoreRegister;
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3 = "";
  in >> key1 >> delIgnReg{'d'};
  if (in)
  {
    value.key1 = key1;
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
  out << value.key1 << "d";
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
