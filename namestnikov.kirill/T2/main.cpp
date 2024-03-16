#include <iostream>
#include <string>
#include <limits>

struct DataStruct
{
  DataStruct(double key1, unsigned long long key2, std::string key3):
    key1_(key1),
    key2_(key2),
    key3_(key3)
  {}
  double get_key1() const
  {
    return key1_;
  }
  unsigned long long get_key2() const
  {
    return key2_;
  }
  std::string get_key3() const
  {
    return key3_;
  }
private:
  double key1_;
  unsigned long long key2_;
  std::string key3_;
};

struct DelimeterChar
{
  char delimeter;
};
struct DelimeterString
{
  const char * delimeter;
};
struct DelimeterLetter
{
  char delimeter;
};


std::istream & operator>>(std::istream & in, DelimeterChar && del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != del.delimeter)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & operator>>(std::istream & in, DelimeterLetter && del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != del.delimeter)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & operator>>(std::istream & in, DelimeterString && del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t i = 0;
  while (del.delimeter[i] != '\0')
  {
    if (std::isalpha(del.delimeter[i]))
    {
      in >> DelimeterLetter{del.delimeter[i]};
    }
    else
    {
      in >> DelimeterChar{del.delimeter[i]};
    }
    ++i;
  }
  return in;
}

std::istream & operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delC = DelimeterChar;
  using delL = DelimeterLetter;
  using delS = DelimeterString;
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3 = "";
  in >> delC{'['} >> key1 >> delL{'u'} >> key2 >> delS{"ull"} >> key3 >> delC{']'};
  if (in)
  {
    data = DataStruct(key1, key2, key3);
  }
  return in;
}

std::ostream & operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "[" << data.get_key1() << ";" << data.get_key2() << ";" << data.get_key3() << "]";
  return out;
}

int main()
{
  DataStruct d(0, 0, "");
  if (!(std::cin >> d))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!(std::cin >> d))
    {
      std::cerr << "Error\n";
      return 1;
    }
  }
}
