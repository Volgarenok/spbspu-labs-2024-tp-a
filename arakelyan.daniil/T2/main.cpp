#include <iostream>

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


int main()
{
  SomeDataS data;
  if (!(std::cin >> data))
  {
    std::cin.clear();
    std::cin.ignore(1);
    if (!(std::cin >> data))
    {
      std::cerr << "Error input\n";
      return 1;
    }
  }
  std::cout << data.a << " - " << data.b << "\n";
  return 0;
}
