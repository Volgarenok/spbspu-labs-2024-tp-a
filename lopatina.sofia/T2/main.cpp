#include <iostream>
#include <string>
#include <limits>
#include <vector>

namespace lopatina
{
  struct DataStruct
  {
    DataStruct(int a, int b):
      a_(a),
      b_(b)
    {}
    int get_a() const
    {
      return a_;
    }
    int get_b() const
    {
      return b_;
    }
  private:
    int a_;
    int b_;
  };

  std::istream & operator>>(std::istream & in, DataStruct & value)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    int a = 0, b = 0;
    in >> a >> b;
    if (in)
    {
      value = DataStruct(a, b);
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
    out << value.get_a() << ' ' << value.get_b();
    return out;
  }
}


int main()
{
  //std::vector<DataStruct> data;
  lopatina::DataStruct d(0, 0);
  std::cin >> d;
  std::cout << d << '\n';
/*
  int a = 0, b = 0;
  char c = 0;
  while (!(std::cin.eof()))
  {
    if (!(std::cin >> a >> b))
    {
      std::cin.clear(std::ios::goodbit);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
      std::cout << a << ' ' << b << '\n';
      return 0;
    }
  }
*/
  return 0;
}
