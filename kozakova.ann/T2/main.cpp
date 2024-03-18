#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

namespace kozakova {
  struct DataStruct
  {
    DataStruct(unsigned long long k1, unsigned long long k2, std::string k3) :
      key1(k1),
      key2(k2),
      key3(k3)
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
    std::string get_Key3() const
    {
      return key3;
    }
    void set_Key1(unsigned long long k1)
    {
      key1 = k1;
    }
    void set_Key2(unsigned long long k2)
    {
      key2 = k2;
    }
    void set_Key3(std::string k3)
    {
      key3 = k3;
    }
  private:
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  struct DelimiterString
  {
    std::string expected;
    bool f;
  };

  std::istream& operator>>(std::istream& in, DelimiterString&& exp)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    std::string s = "";
    if (exp.f)
    {
      std::getline(in, s, ':');
      std::string expUp = exp.expected;
      std::transform(exp.expected.begin(), exp.expected.end(), exp.expected.begin(), ::tolower);
      if ((strcmp(s.c_str(), exp.expected.c_str()) && strcmp(s.c_str(), expUp.c_str())))
      {
        in.setstate(std::ios::failbit);
      }
    }
    else
    {
      in >> s;
      if (strcmp(s.c_str(), exp.expected.c_str()))
      {
        in.setstate(std::ios::failbit);
      }
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

  void setKeys(std::istream& in, std::string key, DataStruct& value)
  {
    using dels = DelimiterString;
    using delc = DelimiterChar;
    if (key == "key1")
    {
      unsigned long long a = 0;
      in >> std::dec >> a >> dels{ "ULL", true };
      if (in)
      {
        value.set_Key1(a);
      }
    }
    else if (key == "key2")
    {
      unsigned long long b = 0;
      in >> delc{ '0' } >> delc{ 'X' } >> std::hex >> b >> delc{ ':' };
      if (in)
      {
        value.set_Key2(b);
      }
    }
    else if (key == "key3")
    {
      std::string s = "";
      in >> delc{ '"' };
      std::getline(in, s, '"');
      in >> delc{ ':' };
      if (in)
      {
        value.set_Key3(s);
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  std::istream& operator>>(std::istream& in, DataStruct& value)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using dels = DelimiterString;
    using delc = DelimiterChar;
    std:: string key = "";
    in >> delc{ '(' } >> delc{ ':' };
    for (int i = 0; i < 3 && in; i++)
    {
      in >> key;
      setKeys(in, key, value);
    }
    in >> delc{ ')' };
    return in;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& value)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    out << "(:key1 " << value.get_Key1() << "ull";
    out << ":key2 " << "0x" << std::uppercase << std::hex << value.get_Key2();
    out << ":key3 \"" << value.get_Key3() << "\":)";
    return out;
  };

}

int main()
{
  kozakova::DataStruct a(0,0, "");
  std::cin >> a;
  std::cout << a;
  return 0;
}