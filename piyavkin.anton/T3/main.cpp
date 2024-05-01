#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "The file is not open\n";
    return 2;
  }
  std::string name = "";
  while (std::cin >> name)
  {
  }
}
