#include <iostream>
#include <string>
#include <list>
#include <iterator>

struct Delimeterchar
{
  char expected;
};

struct Delimeterstring
{
  const char* expected;
};

struct Delimeterpair
{
  char expected;
};

struct DataStruct
{
  double key1;
  std::pair< long long, unsigned long long > key2;
  std::string key3;
  bool operator<(const DataStruct& data) const;
  bool operator>(const DataStruct& data) const;
  bool operator<=(const DataStruct& data) const;
  bool operator>=(const DataStruct& data) const;
  bool operator==(const DataStruct& data) const;
  bool operator!=(const DataStruct& data) const;
};

void inputKeys(std::istream& in, size_t y, DataStruct& data);
std::istream& operator>>(std::istream& in, Delimeterchar&& exp);
std::istream& operator>>(std::istream& in, Delimeterstring&& exp);
std::istream& operator>>(std::istream& in, Delimeterpair&& exp);

std::istream& operator>>(std::istream& in, Delimeterchar&& exp)
{
  std::istream::sentry guard(in);
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, Delimeterstring&& exp)
{
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    if (std::isalpha(exp.expected[i]))
    {
      in >> Delimeterpair{ exp.expected[i++] };
    }
    else
    {
      in >> Delimeterchar{ exp.expected[i++] };
    }
  }
  return in;
}

std::istream& operator>>(std::istream& in, Delimeterpair&& exp)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = 0;
    in >> c;
    c = std::tolower(c);
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& operator>>(std::istream& in, std::string& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    in >> Delimeterchar{ '"' };
    std::getline(in, exp, '"');
  }
  return in;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    using del = Delimeterchar;
    using dell = Delimeterstring;
    in >> del{ '(' };
    size_t keys = 3;
    size_t y = 0;
    for (size_t i = 0; i < keys; ++i)
    {
      in >> dell{ ":key" } >> y;
      inputKeys(in, y, data);
    }
    in >> dell{ ":)" };
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << "(:key1 " << value.key1;
    out << ":key2 (:N " << value.key2.first << ":D " << value.key2.second << ":)";
    out << ":key3 " << '"' << value.key3 << '"' << ":)";
  }
  return out;
}

void inputKeys(std::istream& in, size_t y, DataStruct& data)
{
  using ds = Delimeterstring;
  if (y == 1)
  {
    double num1 = 0;
    in >> num1;
    if (in)
    {
      data.key1 = num1;
    }
  }
  else if (y == 2)
  {
    long long int num = 0;
    unsigned long long den = 0;
    in >> ds{ "(:n" } >> num >> ds{ ":d" } >> den >> ds{ ":)" };
    if (in)
    {
      data.key2.first = num;
      data.key2.second = den;
    }
  }
  else if (y == 3)
  {
    std::string str = "";
    in >> str;
    if (in)
    {
      data.key3 = str;
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
}

bool DataStruct::operator<(const DataStruct& data) const
{
  if (key1 == data.key1)
  {
    if (key2.first * data.key2.second == key2.second * data.key2.first)
    {
      return key3 < data.key3;
    }
    return key2.first * data.key2.second < key2.second * data.key2.first;
  }
  return key1 < data.key1;
}

bool DataStruct::operator>=(const DataStruct& data) const
{
  return !(*this < data);
}

bool DataStruct::operator<=(const DataStruct& data) const
{
  return !(data < *this);
}

bool DataStruct::operator>(const DataStruct& data) const
{
  return (data < *this);
}

bool DataStruct::operator==(const DataStruct& data) const
{
  return !(*this < data) && !(data < *this);
}

bool DataStruct::operator!=(const DataStruct& data) const
{
  return !(data == *this);
}


int main()
{
  using input_it_t = std::istream_iterator< DataStruct >;
  std::list< DataStruct > data(input_it_t{ std::cin }, input_it_t{});
  using output_it_t = std::ostream_iterator< DataStruct >;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{ std::cin }, input_it_t{}, std::back_inserter(data));
  }
  data.sort();
  std::copy(data.cbegin(), data.cend(), output_it_t{ std::cout, "\n" });
}
