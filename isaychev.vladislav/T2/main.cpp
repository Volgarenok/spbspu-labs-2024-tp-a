#include <complex>
#include <iostream>
#include "dataStruct.hpp"
#include "delimeter.hpp"

int main()
{
  using namespace isaychev;
  DataStruct data{};
  std::cin >> data;
  std::cout << data << "\n";
  while (!std::cin.eof())
  {
  }
/*  using ds = delim_str_t;
  using dc = delim_ch_t;
  std::cin >> std::noskipws;
  std::string str = "";
  long long a = 0ll;
  std::cin >> ds{"(:"} >> str >>dc{' '};
  std::getline(std::cin, str, ':');
  std::cin >> ds{")"};
  a = std::stoll(str);
  std::cout << a << "\n";
  if (!std::cin)
  {
    std::cout << "yes\n";
  }
  std::cin >> std::skipws;*/
}
