#include <iostream>
#include <string>

namespace altun
{
  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& del)
  {
    char c = 0;
    in >> c;
    if (c != del.expected)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  struct DataStruct
  {
    double key1;
    double key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    using del = Delimiter;
    int number = 0;
    in >> del{'('};
    int max_keys = 3;
    for (int i = 0; i < max_keys; i++)
    {
      in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
      in >> number;
      if (number == 1)
      {
        in >> data.key1;
      }
      else if (number == 2)
      {
        in >> data.key2;
      }
      else if (number == 3)
      {
        in >> del{'"'};
        std::getline(in, data.key3, '"');
      }
    }
    in >> del{':'} >> del{')'};
    return in;
  }
  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    out << data.key1 << " " << data.key2 << " " << data.key3;
    return out;
  }
}



int main()
{
  using namespace altun;
  DataStruct a{0, 0, ""};
  std::cin >> a;
  std::cout << a << '\n';
}
