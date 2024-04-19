#include <iostream>
#include <fstream>

int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument provided!\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: can't open the file!\n";
    return 2;
  }

  return 0;
}
