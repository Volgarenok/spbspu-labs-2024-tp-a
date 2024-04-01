#include <iostream>
#include <limits>


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

  std::istream &operator>>(std::istream &in, SomeDataS &data)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    int a = 0;
    int b = 0;
    in >> a >> b;
    if (in)
    {
      data = SomeDataS(a,b);
    }
    return in;
  }
}

int main()
{
  using namespace arakelyan;
  SomeDataS data;
  while(!(std::cin >> data))
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::cout << data.a << " - " << data.b << "\n";
  return 0;
}
