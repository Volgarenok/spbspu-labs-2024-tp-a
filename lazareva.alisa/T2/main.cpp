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
      in >> del{'d'};
      data.key1 = value;
      std::cout << data.key1 << "\n";
    }
    else if (i == 2)
    {

    }
    else if (i == 3)
    {

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
