#include <iostream>
#include <limits>
#include <string>


namespace arakelyan
{
  struct SomeDataS
  {
    SomeDataS() = default;
    SomeDataS(int aa, int bb):
      a(aa),
      b(bb)
    {}
    int a;
    int b;
  };

  //format: key:10; key:20
  std::istream &operator>>(std::istream &in, SomeDataS &data)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    std::string c = "";
    int a = 0;
    int b = 0;
    in >> c >> a >> b;
    if (c != "keys:")
    {
      in.setstate(std::ios::failbit);
    }
    if (in)
    {
      data = SomeDataS(a,b);
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const SomeDataS &data)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    out << "key1:" << data.a << "; " << "key2:" << data.b;
    return out;
  }
}

int main()
{
  using namespace arakelyan;
  SomeDataS data;
  while(!(std::cin >> data))
  {
    if (!(std::cin))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::cout << data << "\n";
  return 0;
}
