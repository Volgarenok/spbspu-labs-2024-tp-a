#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
namespace kozakova {
  struct Data
  {
    Data(unsigned long long k1, unsigned long long k2) :
      key1(k1),
      key2(k2)
    {
    }
    unsigned long long get_Key1() const
    {
      return key1;
    }
    unsigned long long get_Key2() const
    {
      return key2;
    }
  private:
    unsigned long long key1;
    unsigned long long key2;
    //std::string key3;
  };

  struct DelimiterString
  {
    std::string expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    std::string s = "";
    std::string expUp = exp.expected;
    std::transform(exp.expected.begin(), exp.expected.end(), exp.expected.begin(), ::tolower);
    in >> s;
    if ((strcmp(s.c_str(), exp.expected.c_str()) && strcmp(s.c_str(), expUp.c_str()))) 
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  };

  struct DelimiterChar
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterChar&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    char c = 0;
    in >> c;
    if (!(c == exp.expected || c == tolower(exp.expected)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  };

  std::istream& operator>>(std::istream& in, Data& value)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using dels = DelimiterString;
    using delc = DelimiterChar;
    unsigned long long a = 0;
    unsigned long long b = 0;
    in >> a >> dels{ "ULL" } >> delc{ '0' } >> delc{ 'X' } >> std::hex >> b;
    if (in)
    {
      value = Data(a, b);
    }
    return in;
  };

  std::ostream& operator<<(std::ostream& out, const Data& value)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    out << value.get_Key1() << "ull" << " " << "0x" << std::uppercase << std::hex << value.get_Key2();
    return out;
  };
}

int main()
{
  kozakova::Data a(0,0);
  std::cin >> a;
  std::cout << a;
  return 0;
}