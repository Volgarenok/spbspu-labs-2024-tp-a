#include <iostream>
#include <limits>

int main()
{
  int a = 0, b = 0;
  char c = 0;
  if (!(std::cin >> a >> b))
  {
    std::cin.clear(std::ios::goodbit);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!(std::cin >> a >> b))
    {
      std::cerr << "Error\n";
      return 1;
    }
  }
  std::cout << a << ' ' << b << '\n';
  return 0;
}
