#include <iostream>
#include <string>

namespace lazareva
{

  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& exp)
  {
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  return in;
  }

  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    using del = lazareva::Delimiter;
    in >> del{'('} >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
    int i = 0;
    in >> i;
    if (i == 1)
    {
      double value = 0;
      in >> value;
      data.key1 = value;
      in >> del{'d'};
    }
    else if (i == 2)
    {
      long long value = 0;
      in >> value;
      data.key2 = value;
      in >> del{'l'} >> del{'l'};
    }
    else if (i == 3)
    {
      std::string value = "";
      in >> del{'"'};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}

int main()
{
  lazareva::DataStruct datastruct{0,0,""};
  std::cin >> datastruct;

}
