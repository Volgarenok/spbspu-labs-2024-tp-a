#include <iostream>
#include <fstream>

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }
  else
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Can not open file\n";
      return 1;
    }
  }
}
