#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "dataStruct.hpp"
#include "delimeter.hpp"

int main()
{
  using namespace isaychev;
  using in_it_t = std::istream_iterator< DataStruct >;
//  using out_it_t = std::ostream_iterator< DataStruct >;

  std::vector< DataStruct > vec{};
  while (!std::cin.eof())
  {
    std::copy(in_it_t{std::cin}, in_it_t{}, std::back_inserter(vec));
    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::cout << vec.size() << "\n";
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
