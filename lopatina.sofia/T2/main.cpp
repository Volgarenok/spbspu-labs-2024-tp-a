#include <iostream>
#include <limits>

int main()
{
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
}
