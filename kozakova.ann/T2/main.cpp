#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
namespace kozakova {
  struct Data
  {
    Data(unsigned long long k) :
      key1(k)
    {
    }
    unsigned long long get_Key1() const
    {
      return key1;
    }
  private:
    unsigned long long key1;
    //unsigned long long key2;
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
    if ((strcmp(s.c_str(), exp.expected.c_str()) && strcmp(s.c_str(), expUp.c_str()))) // подумать
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
    using del = DelimiterString;
    unsigned long long a = 0;
    in >> a >> del{ "ULL" };
    if (in)
    {
      value = Data(a);
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
    out << value.get_Key1() << "ull";
    return out;
  };
}

int main()
{
  kozakova::Data a(0);
  std::cin >> a;
  std::cout << a;
  return 0;
}