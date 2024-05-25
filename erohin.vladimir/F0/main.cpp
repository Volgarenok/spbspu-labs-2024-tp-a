#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  std::string format_arg(argv[1]);
  if (format_arg.substr(0, 12) == "--numformat=")
  {
    std::cout << format_arg.substr(12) << "\n";
  }
  else
  {
    std::cerr << "Wrong number format\n";
    return 2;
  }
  return 0;
}
