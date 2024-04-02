#include <iostream>

int main()
{
  int a = 0, b = 0;
  if (!(std::cin >> a >> b))
  {
    std::cin.clear();
    std::cin.ignore(1);
    if (!(std::cin >> a >> b))
    {
      std::cerr << "Error\n";
      return 1;
    }
  }
  std::cout << a << " " << b << '\n';
  return 0;
}
