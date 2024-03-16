#include <complex>
#include <iostream>
//#include "dataStruct.hpp"
#include "delimeter.hpp"
namespace isaychev
{
  using dc = delim_ch_t;
  using ds = delim_str_t;

  struct two
  {
    int a;
    int b;
  };

  std::istream & operator>>(std::istream & in, two & t)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    in >> ds{"(:"} >> t.a >> dc{' '} >> t.b >> ds{":)"};
    if (!in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}

int main()
{
/*  using namespace isaychev;
  std::complex< double > num1(12.2, 3.0);
  std::string str = "Data";
  long long num2 = 10ll;
  DataStruct data{num2, num1, str};
  std::cout << data << "\n";*/
  using namespace isaychev;
  std::cin >> std::noskipws;
  two t{};
  std::cin >> t;
  std::cin >> std::skipws;
  std::cout << t.a << " " << t.b << "\n";
}
